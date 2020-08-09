load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

cmake_external(
    name = "ntcore",
    cache_entries = {
        "WITHOUT_JAVA": "ON",
        "BUILD_SHARED_LIBS": "ON",
        "WITHOUT_CSCORE": "ON",
    },
    lib_source = "@wpilib_sources//:all",
    out_include_dir = "wpilib/include/ntcore",
    out_lib_dir = "wpilib/lib",
    shared_libraries = ["libntcore.so"],
    visibility = ["//visibility:public"],
    deps = [
        ":wpiutil"
    ]
)

cmake_external(
    name = "wpiutil",
    cache_entries = {
        "WITHOUT_JAVA": "ON",
        "BUILD_SHARED_LIBS": "ON",
        "WITHOUT_CSCORE": "ON",
    },
    lib_source = "@wpilib_sources//:all",
    out_include_dir = "wpilib/include/wpiutil",
    out_lib_dir = "wpilib/lib",
    shared_libraries = ["libwpiutil.so"],
    visibility = ["//visibility:public"],
)

