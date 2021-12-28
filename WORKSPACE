workspace(name = "tensor-api-security")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

PROXY_WASM_CPP_SDK_SHA = "fd0be8405db25de0264bdb78fae3a82668c03782"
PROXY_WASM_CPP_SDK_SHA256 = "c57de2425b5c61d7f630c5061e319b4557ae1f1c7526e5a51c33dc1299471b08"

http_archive(
    name = "proxy_wasm_cpp_sdk",
    sha256 = PROXY_WASM_CPP_SDK_SHA256,
    strip_prefix = "proxy-wasm-cpp-sdk-" + PROXY_WASM_CPP_SDK_SHA,
    url = "https://github.com/proxy-wasm/proxy-wasm-cpp-sdk/archive/" + PROXY_WASM_CPP_SDK_SHA + ".tar.gz",
)


load("@proxy_wasm_cpp_sdk//bazel/dep:deps.bzl", "wasm_dependencies")

wasm_dependencies()

http_archive(
   name = "rules_foreign_cc",
   strip_prefix = "rules_foreign_cc-4010620160e0df4d894b61496d3d3b6fc8323212",
    sha256 = "07e3414cc841b1f4d16e5231eb818e5c5e03e2045827f5306a55709e5045c7fd",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/4010620160e0df4d894b61496d3d3b6fc8323212.zip",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

load("@proxy_wasm_cpp_sdk//bazel/dep:deps_extra.bzl", "wasm_dependencies_extra")

wasm_dependencies_extra()

git_repository(
    name = "rules_perl",
    remote = "https://github.com/bazelbuild/rules_perl.git",
    branch = "master",
)

load("@rules_perl//perl:deps.bzl", "perl_register_toolchains", "perl_rules_dependencies",)

perl_rules_dependencies()
perl_register_toolchains()

load("//bazel:openssl_repositories.bzl", "openssl_repositories")

openssl_repositories()

load("//bazel:openssl_setup.bzl", "openssl_setup")

openssl_setup()

load("//bazel:protobuf_c_repositories.bzl", "protobuf_c_libraries")

protobuf_c_libraries()

load("//bazel:nats_repositories.bzl", "nats_c_libraries")

nats_c_libraries()