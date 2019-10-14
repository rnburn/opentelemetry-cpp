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
    deps = [
        "//:opentelemetry_lib",
    ],
)

opentelemetry_catch_test(
    name = "string_view_test",
    srcs = [
        "string_view_test.cpp",
    ],
    deps = [
        "//:opentelemetry_lib",
    ],
)

opentelemetry_catch_test(
    name = "attribute_value_test",
    srcs = [
        "attribute_value_test.cpp",
    ],
    deps = [
        "//:opentelemetry_lib",
    ],
)

opentelemetry_catch_test(
    name = "timestamp_test",
    srcs = [
        "timestamp_test.cpp",
    ],
    deps = [
        "//:opentelemetry_lib",
    ],
)
