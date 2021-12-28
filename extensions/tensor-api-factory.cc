#include "envoy/http/filter.h"
#include "envoy/server/filter_config.h"

#include "src/tensor-api-security/security_config.pb.h"
#include "src/tensor-api-security/security_config.pb.validate.h"

#include "api_security.h"

namespace Envoy {
namespace Entexsions {
namespace HttpFilters {
namespace ApiSecurity {

class HttpApiSecurityConfigFacory : public Server::Configuration::NamedHttpFilterConfigFactory,
                                    public Logger::Loggable<Logger::Id::config> {
private:
  /* data */
  std::shared_ptr<BlockingQueue<security::ApiInfo>> queue_;
  std::shared_ptr<Extensions::HttpFilters::ApiSecurity::NatsPublisher> publisher_;

public:
  HttpApiSecurityConfigFacory(/* args */);
  ~HttpApiSecurityConfigFacory();
  Http::FilterFactoryCb
  createFilterFactoryFromProto(const Protobuf::Message& proto_config, const std::string&,
                               Server::Configuration::FactoryContext& context) override

  {
    auto config = Envoy::MessageUtil::downcastAndValidate<const security::SecurityConfig&>(
        proto_config, context.messageValidationVisitor());
    auto configPtr = std::make_shared<Extensions::HttpFilters::ApiSecurity::ApiSecurityConfig>(
        Extensions::HttpFilters::ApiSecurity::ApiSecurityConfig(config));
    ENVOY_LOG(debug, "create new api-security filter");

    if (publisher_ == nullptr) {
      publisher_ = std::make_shared<Extensions::HttpFilters::ApiSecurity::NatsPublisher>(
          config.urls(), config.subject(), config.clientid());
      publisher_->initialize();
    }

    return [this, configPtr](Http::FilterChainFactoryCallbacks& callbacks) -> void {
      callbacks.addStreamFilter(Http::StreamFilterSharedPtr{
          new Extensions::HttpFilters::ApiSecurity::ApiSecurityFilter(configPtr, publisher_)});
    };
  }

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new security::SecurityConfig{}};
  }

  std::string name() const override { return "api-security"; }
};

HttpApiSecurityConfigFacory::HttpApiSecurityConfigFacory(/* args */) {
  ENVOY_LOG(info, "create message queue");
  // queue_ = std::make_shared<BlockingQueue<security::ApiInfo>>();
}

HttpApiSecurityConfigFacory::~HttpApiSecurityConfigFacory() {}

/**
 * Static registration for this sample filter. @see RegisterFactory.
 */
static Registry::RegisterFactory<HttpApiSecurityConfigFacory,
                                 Server::Configuration::NamedHttpFilterConfigFactory>
    register_;

} // namespace ApiSecurity
} // namespace HttpFilters
} // namespace Entexsions
} // namespace Envoy
