"""A module defining the third party dependency nats.c"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def nats_c_libraries():
    http_archive(
      name = "nats",
      sha256 = "40f72e9b66b44649c4caf0d06e8c4968c3a0ed93c87b48195a0c8c53f8f41c52",
      strip_prefix = "nats.c-3.1.1",
      url = "https://github.com/nats-io/nats.c/archive/refs/tags/v3.1.1.tar.gz",
      build_file = Label("//third-party:nats.BUILD"),
   )