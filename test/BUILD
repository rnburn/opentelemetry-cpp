load(
    "//bazel:opentelemetry_build_system.bzl",
    "opentelemetry_catch_test",
    "opentelemetry_package",
)

opentelemetry_package()

opentelemetry_catch_test(
    name = "variant_test",
    srcs = [
        "variant_test.cpp",
    ],
)
