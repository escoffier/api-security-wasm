"""An openssl build file based on a snippet found in the github issue:
https://github.com/bazelbuild/rules_foreign_cc/issues/337
"""

load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

# load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")

# Read https://wiki.openssl.org/index.php/Compilation_and_Installation
package(default_visibility = ["//visibility:public"])

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

CONFIGURE_OPTIONS = [
    "no-comp",
    "no-idea",
    "no-weak-ssl-ciphers",
    "no-shared",
    "no-asm",
]

LIB_NAME = "openssl"

MAKE_TARGETS = [
    "build_libs",
    "install_dev",
]


configure_make(
    name = "openssl_default",
    configure_command = "config",
    configure_in_place = True,
    configure_options = CONFIGURE_OPTIONS,
    # env = select({
    #     "@platforms//os:macos": {
    #         "AR": "",
    #         "PERL": "$$EXT_BUILD_ROOT$$/$(PERL)",
    #     },
    #     "//conditions:default": {
    #         "PERL": "$$EXT_BUILD_ROOT$$/$(PERL)",
    #     },
    # }),
    lib_name = LIB_NAME,
    lib_source = ":all_srcs",
    # Note that for Linux builds, libssl must come before libcrypto on the linker command-line.
    # As such, libssl must be listed before libcrypto
    out_static_libs = [
        "libssl.a",
        "libcrypto.a",
    ],
    targets = MAKE_TARGETS,
    toolchains = ["@rules_perl//:current_toolchain"],
)

filegroup(
    name = "gen_dir",
    srcs = [":openssl"],
    output_group = "gen_dir",
    visibility = ["//visibility:public"],
)