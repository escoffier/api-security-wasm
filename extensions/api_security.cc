#include "api_security.h"
#include "src/tensor-api-security/api_info.pb.h"

static RegisterContextFactory register_gRPCLogging(CONTEXT_FACTORY(ApiInfoContext),
                                                   ROOT_FACTORY(ApiInfoRootContext));

bool ApiInfoRootContext::onStart(size_t) {}

bool ApiInfoRootContext::onConfigure(size_t) {
  publisher_ =
      std::make_unique<NatsPublisher>("nats://localhost:4222", "apt-security", "test-client");
  publisher_.initialize();
}

void ApiInfoRootContext::onTick() {}

// ApiInfoContext
void ApiInfoContext::onCreate() {}

FilterHeadersStatus ApiInfoContext::onRequestHeaders(uint32_t headers, bool end_of_stream) {}

FilterDataStatus ApiInfoContext::onRequestBody(size_t body_buffer_length, bool end_of_stream) {}

FilterHeadersStatus ApiInfoContext::onResponseHeaders(uint32_t headers, bool end_of_stream) {}

FilterDataStatus ApiInfoContext::onResponseBody(size_t body_buffer_length, bool end_of_stream) {}

void ApiInfoContext::onDone() {}

void ApiInfoContext::onLog() {
  security::ApiInfo api_info;
  getValue({"request", "url_path"}, api_info.mutable_path());
  rootContext()->publish(api_info);

}

void ApiInfoContext::onDelete() {}