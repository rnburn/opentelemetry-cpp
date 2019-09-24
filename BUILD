load(
    "//bazel:opentelemetry_build_system.bzl",
    "opentelemetry_cc_library",
    "opentelemetry_package",
)

opentelemetry_package()

opentelemetry_cc_library(
    name = "opentelemetry_lib",
    hdrs = glob(["include/**/*.h"]),
    strip_include_prefix = "include",
    deps = [
        "//3rd_party/mpark:variant_lib",
    ],
)

