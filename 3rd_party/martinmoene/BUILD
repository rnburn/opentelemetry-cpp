load(
    "//bazel:opentelemetry_build_system.bzl",
    "opentelemetry_cc_library",
    "opentelemetry_package",
)

opentelemetry_package()

opentelemetry_cc_library(
    name = "string_view_lib",
    hdrs = glob(["include/**/*.h"]),
    strip_include_prefix = "include",
)

