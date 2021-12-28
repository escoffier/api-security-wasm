load("@proxy_wasm_cpp_sdk//bazel/wasm:wasm.bzl", "wasm_cc_binary")


licenses(["notice"])  # Apache 2

wasm_cc_binary(
    name = "envoy_filter_http_wasm.wasm",
    # srcs = [
    #     # "plugin.cc",
    #     # "plugin.h",
    #     "nats_publisher.h",
    #     "api_security.h",
    #     "api_security.cc", 
    #     "nats_publisher.cc"
    # ],
    deps = [
        # ":config_cc_proto",
        # ":api_info_cc_proto",
        "//extensions:http-api-filter",
        # "@com_google_absl//absl/strings",
        "@proxy_wasm_cpp_sdk//:proxy_wasm_intrinsics_lite",
        # "@openssl//:openssl_default",
        "@protobuf-c//:libprotobuf-c",
        # "@nats//:libnats",
        # ":pkg_cc_proto",
    ],
)