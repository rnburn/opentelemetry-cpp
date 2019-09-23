load(
    "//bazel:opentelemetry_build_system.bzl",
    "opentelemetry_cc_library",
    "opentelemetry_package",
)

opentelemetry_package()

opentelemetry_cc_library(
    name = "catch2_lib",
    hdrs = [
        "catch.hpp",
    ],
)

opentelemetry_cc_library(
    name = "main_lib",
    srcs = [
        "catch_main.cpp",
    ],
    deps = [
        ":catch2_lib",
    ],
)

