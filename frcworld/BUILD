load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "frcworld",
    srcs = [
        "main.cc",
        "json.hpp",
        "cxxopts.hpp"
    ],
    deps = [
        "//thirdparty/ntcore",
        "//thirdparty/raylib",
    ],
    copts=["-std=c++17"]
)
