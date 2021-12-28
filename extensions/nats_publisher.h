#pragma once

#include <atomic>
#include <memory>
#include <string>
#include <thread>

// #include "common/common/logger.h"
#include "src/tensor-api-security/api_info.pb.h"
// #include "blockingqueue.h"

// #include "envoy/common/commnon/base_logger"
#define NATS_HAS_STREAMING
extern "C" {
#include <nats/nats.h>
}

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace ApiSecurity {

using BlockingQueueSharedPtr = std::shared_ptr<BlockingQueue<security::ApiInfo>>;

class NatsPublisher {
public:
  NatsPublisher(const std::string& urls, const std::string& subject, const std::string& clientId)
      : urls_(urls), subject_(subject), stanOpts_(nullptr), natsOpts_(nullptr),
        stanConnection_(nullptr), clientId_(clientId) {};

  ~NatsPublisher() {
    natsOptions_Destroy(natsOpts_);
    stanConnOptions_Destroy(stanOpts_);
    quit();
  };

  bool initialize();
  bool connect();
  void run();
  void publish(const void* data, int dataLen);
  void publish(const security::ApiInfo& apiInfo);

  void quit() {
    // ENVOY_LOG(debug, "Quitting Nats publisher");
    // quit_.store(true);
    // queue_->quit();
    // if (started_) {
    //   workerThread_.join();
    // }
  }

private:
  std::string urls_;
  std::string subject_;
  // natsConnection* natsConn_;
  stanConnOptions* stanOpts_;
  natsOptions* natsOpts_;
  stanConnection* stanConnection_;
  std::string clientId_;

  // BlockingQueueSharedPtr queue_;
  //   BlockingQueue<security::ApiInfo> queue_;
  // std::thread workerThread_;
  // std::atomic<bool> quit_;
  // std::atomic<bool> started_;
public:
  static bool connLost_;
};
} // namespace ApiSecurity
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy