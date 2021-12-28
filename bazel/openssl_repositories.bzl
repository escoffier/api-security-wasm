"""A module defining the third party dependency OpenSSL"""

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
# load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

def openssl_repositories():
    http_archive(
        name = "openssl",
        build_file = Label("//third-party:openssl.BUILD"),
        sha256 = "892a0875b9872acd04a9fde79b1f943075d5ea162415de3047c327df33fbaee5",
        strip_prefix = "openssl-1.1.1k",
        urls = [
            "https://mirror.bazel.build/www.openssl.org/source/openssl-1.1.1k.tar.gz",
            "https://www.openssl.org/source/openssl-1.1.1k.tar.gz",
            "https://github.com/openssl/openssl/archive/OpenSSL_1_1_1k.tar.gz",
        ],
    )