load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cmake_external(
    name = "raylib",
    cache_entries = {
        "SHARED": "ON",
        "STATIC":"ON",
        "USE_AUDIO":"ON",
        "SUPPORT_FILEFORMAT_BMP":"ON",
        "SUPPORT_FILEFORMAT_JPG":"ON",
        "SUPPORT_FILEFORMAT_FLAC":"ON"
    },
    lib_source = "@raylib_sources//:all",
    # static_libraries = ["libraylib.a"],
    shared_libraries = ["libraylib.so.301"],
    visibility = ["//visibility:public"],
)
