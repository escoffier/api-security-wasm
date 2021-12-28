
# load("@envoy//bazel:envoy_build_system.bzl", "envoy_cmake_external", "envoy_package")

# envoy_package()

# load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")
load("@rules_foreign_cc//tools/build_defs:configure.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

cmake(
    name = "libnats",
    cache_entries = {
        "CMAKE_BUILD_TYPE": "Release",
        "RUN_TEST": "off",
        "CMAKE_INSTALL_LIBDIR": "lib",
    },
    lib_source = ":all_srcs",
    out_static_libs = ["libnats_static.a"],
    tags = ["skip_on_windows"],
    deps = [
        "@openssl//:ssl", 
        "@protobuf-c//:libprotobuf-c"
        ],
)

# envoy_cmake_external(
#     name = "libnats-no-ssl",
#     cache_entries = {
#         "CMAKE_BUILD_TYPE": "Release",
#         "RUN_TEST": "off",
#         "CMAKE_INSTALL_LIBDIR": "lib",
#     },
#     lib_source = ":all_srcs",
#     static_libraries = ["libnats_static.a"],
#     tags = ["skip_on_windows"],
#     deps = [
#         # "@boringssl//:ssl", 
#         "@protobuf-c//:libprotobuf-c"
#         ],
# )