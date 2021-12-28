# load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

package(default_visibility = ["//visibility:public"])
# cc_library(
#     name = "libprotobuf-c",
#     srcs = ["libprotobuf-c.a"],
# )
filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

configure_make(
    name = "libprotobuf-c",
    autogen = True,
    configure_in_place = True,
    # configure_command = "autogen.sh && configure",
    configure_options = [
        # "--disable-dependency-tracking",
    ],
    # configure_options = [
    #     "--enable-shared=no",
    #     "--enable-frame-pointers",
    #     "--disable-libunwind",
    # ] + select({
    #     "//bazel:apple": ["AR=/usr/bin/ar"],
    #     "//conditions:default": [],
    # }),
    lib_source = ":all_srcs",
    # linkopts = ["-lpthread"],
    # make_commands = ["make && make install"],
    out_static_libs = ["libprotobuf-c.a"],
    tags = ["skip_on_windows"],
    # deps = ["@com_google_protobuf//:protoc"]
)