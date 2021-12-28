# load("@bazel_skylib//lib:selects.bzl", "selects")
# load(
#     "@envoy//bazel:envoy_build_system.bzl",
#     "envoy_package",
# )
# load("@envoy//bazel/wasm:wasm.bzl", "envoy_wasm_cc_binary")
# load("@envoy_api//bazel:api_build_system.bzl", "api_proto_package")

# load("@proxy_wasm_cpp_sdk//bazel/wasm:wasm.bzl", "wasm_cc_binary")

package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2

# envoy_package()

# api_proto_package(
#     srcs = [
#         "security_config.proto",
#         "api_info.proto",
#         ],
#     deps = [
#         "@envoy_api//envoy/config/core/v3:pkg",
#     ],
# )

cc_proto_library(
    name = "config_cc_proto",
    deps = [":config_proto"],
)

proto_library(
    name = "config_proto",
    srcs = ["security_config.proto"],
)

cc_proto_library(
    name = "api_info_cc_proto",
    deps = [":api_info_proto"],
)

proto_library(
    name = "api_info_proto",
    srcs = ["api_info.proto"],
)


# wasm_cc_binary(
cc_binary(
    # name = "envoy_filter_http_wasm_example.wasm",
    name = "http-api-filter",
    srcs = [
        # "plugin.cc",
        # "plugin.h",
        "nats_publisher.h",
        "api_security.h",
        "api_security.cc", 
        "nats_publisher.cc"
    ],
    deps = [
        ":config_cc_proto",
        ":api_info_cc_proto",
        # "@com_google_absl//absl/strings",
        # "@proxy_wasm_cpp_sdk//:proxy_wasm_intrinsics_lite",
        # # "@openssl//:openssl_default",
        # "@protobuf-c//:libprotobuf-c",
        # "@nats//:libnats",
    ],
)


# filegroup(
#     name = "configs",
#     srcs = glob([
#         "**/*.wasm",
#     ]) + select({
#         ":include_wasm_config": glob(
#             [
#                 "**/*.yaml",
#             ],
#             exclude = [
#                 "**/*docker-compose*.yaml",
#             ],
#         ),
#         "//conditions:default": [],
#     }),
# )

# envoy_wasm_cc_binary(
#     name = "envoy_filter_http_wasm_example.wasm",
#     srcs = [
#         "nats_publisher.h",
#         "api_security.h",
#         "api_security.cc", 
#         "nats_publisher.cc"
#     ],
#     deps = [
#         # "@envoy//bazel:boringssl",
#         # "@boringssl//:crypto",
#         # "@boringssl//:ssl",
#         "@openssl//:openssl_default",
#         "@protobuf-c//:libprotobuf-c",
#         "@nats//:libnats-no-ssl",
#         ":pkg_cc_proto",
#         "@envoy//source/common/common:minimal_logger_lib",
#     ],
# )

# # envoy_wasm_cc_binary(
# #     name = "envoy_filter_http_wasm_updated_example.wasm",
# #     srcs = ["envoy_filter_http_wasm_updated_example.cc"],
# # )

# filegroup(
#     name = "files",
#     srcs = glob(["**/*"]),
# )
