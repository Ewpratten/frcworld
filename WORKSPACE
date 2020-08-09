workspace(name = "frcworld")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Group the sources of the library so that CMake rule have access to it
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# Rule repository
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

http_archive(
    name = "raylib_sources",
    build_file_content = all_content,
    sha256 = "164d1cc1710bb8e711a495e84cc585681b30098948d67d482e11dc37d2054eab",
    strip_prefix = "raylib-3.0.0",
    url = "https://github.com/raysan5/raylib/archive/3.0.0.tar.gz",
)

http_archive(
    name = "wpilib_sources",
    build_file_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])""",
    sha256 = "9df94fd4c3f3a76201619cdb4010fdb923b6ed28a235dde3bf98e36539464f40",
    strip_prefix = "allwpilib-2020.3.2",
    url = "https://github.com/wpilibsuite/allwpilib/archive/v2020.3.2.tar.gz",
)
