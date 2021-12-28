#include <string>
#include <string_view>
#include <unordered_map>
#include <memory>

#include "proxy_wasm_intrinsics.h"
#include "nats_publisher.h"

using namespace Envoy::Extensions::HttpFilters::ApiSecurity;

class ApiInfoRootContext : public RootContext {
public:
  bool onStart(size_t) override;
  bool onConfigure(size_t) override;
  void onTick() override;
  void publish(const security::ApiInfo& apiInfo);

private:
  std::unique_ptr<NatsPublisher> publisher_;
};

class ApiInfoContext : public Context {
public:
  explicit ApiInfoContext(uint32_t id, RootContext* root) : Context(id, root) {}
  void onCreate() override;
  FilterHeadersStatus onRequestHeaders(uint32_t headers, bool end_of_stream) override;
  FilterDataStatus onRequestBody(size_t body_buffer_length, bool end_of_stream) override;
  FilterHeadersStatus onResponseHeaders(uint32_t headers, bool end_of_stream) override;
  FilterDataStatus onResponseBody(size_t body_buffer_length, bool end_of_stream) override;
  void onDone() override;
  void onLog() override;
  void onDelete() override;

private:
  inline ApiInfoRootContext* rootContext() {
    return dynamic_cast<ApiInfoRootContext*>(this->root());
  }
};