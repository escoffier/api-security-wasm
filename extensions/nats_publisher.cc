#include <iostream>
#include <nats/status.h>
#include <thread>

// #include "common/common/logger.h"
// #include "src/tensor-api-security/api_info.pb.h"
// #include "blockingqueue.h"

// #include "envoy/common/commnon/base_logger"
#include "nats_publisher.h"
#include "src/tensor-api-security/api_info.pb.h"

extern "C" {
#include <nats/nats.h>
}

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace ApiSecurity {

const char* NATS_CLUSTER_ID = "tensorsec";

void connectionLostCB(stanConnection* sc, const char* errTxt, void*) {
  NatsPublisher::connLost_ = true;

  std::cout << "connection lost: " << errTxt << std::endl;

  natsConnection* nc;
  if (stanConnection_GetNATSConnection(sc, &nc) != NATS_OK) {
    nats_PrintLastErrorStack(stdout);
    return;
  }
  natsConnStatus cstatus = natsConnection_Status(nc);
  std::cout << "Connection status: " << cstatus << std::endl;

  nats_PrintLastErrorStack(stdout);
}

bool NatsPublisher::connLost_ = true;

bool NatsPublisher::initialize() {

  // ENVOY_LOG(debug, "nats url: {}", urls_);
  natsStatus s;

  const char* serverUrls[1];
  if (natsOptions_Create(&natsOpts_) != NATS_OK) {
    // ENVOY_LOG(error, "failed to create nats connection options");
    return false;
  }
  serverUrls[0] = urls_.c_str();

  if (natsOptions_SetServers(natsOpts_, static_cast<const char**>(serverUrls), 1) != NATS_OK) {
    // ENVOY_LOG(error, "failed to set nats server");
    return false;
  }

  if (natsOptions_SetAllowReconnect(natsOpts_, true) != NATS_OK) {
    // ENVOY_LOG(error, "failed to set nats allow reconnect");
    return false;
  }
  natsOptions_SetReconnectedCB(
      natsOpts_,
      [](natsConnection* nc, void*) {
        // ENVOY_LOG(error, "reconncecting: {}", natsConnection_Status(nc));
      },
      NULL);
  natsOptions_SetReconnectBufSize(natsOpts_, 10000);
  natsOptions_SetReconnectWait(natsOpts_, 500);
  natsOptions_SetMaxReconnect(natsOpts_, 100000);

  if (stanConnOptions_Create(&stanOpts_) != NATS_OK) {
    // ENVOY_LOG(error, "failed to create stan connection options");
    return false;
  }

  if (stanConnOptions_SetNATSOptions(stanOpts_, natsOpts_) != NATS_OK) {
    // ENVOY_LOG(error, "failed to set nast opt ");
    return false;
  }

  stanConnOptions_SetPings(stanOpts_, 5, 3);

  if (stanConnOptions_SetURL(stanOpts_, urls_.c_str()) != NATS_OK) {
    // ENVOY_LOG(error, "failed to set stan connection url {}", urls_);
    return false;
  }

  natsConnection* nc;
  s = natsConnection_Connect(&nc, natsOpts_);
  if (s != NATS_OK) {
    // ENVOY_LOG(error, "failed to connect to nats server {}", urls_);
  }

  stanConnOptions_SetConnectionLostHandler(stanOpts_, connectionLostCB, stanOpts_);

  s = stanConnection_Connect(&stanConnection_, NATS_CLUSTER_ID, clientId_.c_str(), stanOpts_);
  if (s != NATS_OK) {
    // ENVOY_LOG(error, "failed to connect to stan: {}", natsStatus_GetText(s));
    nats_PrintLastErrorStack(stdout);
    return false;
  }
  // ENVOY_LOG(info, "successfully connected to stan: {}", urls_);
  connLost_ = false;
  return true;
}

bool NatsPublisher::connect() {
  if (connLost_) {
    // ENVOY_LOG(info, "try to connect to stan: {}", urls_);
    natsStatus s = stanConnection_Connect(&stanConnection_, NATS_CLUSTER_ID, clientId_.c_str(), stanOpts_);
    if (s != NATS_OK) {
      // ENVOY_LOG(error, "failed to connect to stan: {}", natsStatus_GetText(s));
      nats_PrintLastErrorStack(stdout);
      return false;
    }
    connLost_ = false;
  }
  return true;
}

void NatsPublisher::publish(const void* data, int dataLen) {
  connect();
  if (stanConnection_ != nullptr) {
    // ENVOY_LOG(debug, "publish message to stan");
    natsStatus s = stanConnection_PublishAsync(stanConnection_, subject_.c_str(), data, dataLen,
                                               nullptr, nullptr);
    if (s != NATS_OK) {
      // ENVOY_LOG(error, "failed sending message: {}", natsStatus_GetText(s));
    }
  }
}

void NatsPublisher::publish(const security::ApiInfo& api_info) {
  connect();
  if (stanConnection_ != nullptr) {
    char buf[1024 * 1024];
    size_t size = api_info.ByteSizeLong();
    // ENVOY_LOG(debug, "ApiInfo: {}", api_info.DebugString());
    api_info.SerializeToArray(buf, size);
    natsStatus s =
        stanConnection_PublishAsync(stanConnection_, subject_.c_str(), buf, size, nullptr, nullptr);
    if (s != NATS_OK) {
      // ENVOY_LOG(error, "failed sending message: {}", natsStatus_GetText(s));
    }
  }
}

} // namespace ApiSecurity
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy