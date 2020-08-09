load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "frcworld",
    srcs = [
        "cxxopts.hpp",
        "json.hpp",
        "main.cc",
    ],
    copts = [
        "-std=c++17",
        "-fpermissive",
    ],
    deps = [
        "//thirdparty/ntcore",
        "//thirdparty/raylib",
    ],
)
