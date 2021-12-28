"""A module defining the third party dependency protobuf-c"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def protobuf_c_libraries():
    http_archive(
       name = "protobuf-c",
       # sha256 = "26d98ee9bf18a6eba0d3f855ddec31dbe857667d269bc0b6017335572f85bbcb",
       sha256 = "1068bca1e9870e9492096f97c409cd15f10c5019c183e52ec6d53e8d18630cbf",
       strip_prefix = "protobuf-c-1.4.0",
       url = "https://github.com/protobuf-c/protobuf-c/archive/refs/tags/v1.4.0.tar.gz",
       # url = "https://github.com/protobuf-c/protobuf-c/releases/download/v1.4.0/protobuf-c-1.4.0.tar.gz",
       build_file = Label("//third-party:protobufc.BUILD"),
    )
