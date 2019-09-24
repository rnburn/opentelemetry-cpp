def opentelemetry_copts():
  return [
      "-Wall",
      "-Wextra",
      "-Werror",
      "-Wnon-virtual-dtor",
      "-Woverloaded-virtual",
      "-Wold-style-cast",
      "-Wno-overloaded-virtual",
      "-Wvla",
      "-std=c++11",
  ]

def opentelemetry_package():
    native.package(default_visibility = ["//visibility:public"])

def opentelemetry_cc_library(name, copts = [], *args, **kwargs):
  native.cc_library(
      name = name, 
      copts = opentelemetry_copts() + copts,
      *args, 
      **kwargs,
  )

def opentelemetry_catch_test(name, deps = [], copts = [], *args, **kwargs):
  native.cc_test(
      name = name,
      deps = deps + ["//3rd_party/catch2:main_lib"],
      copts = opentelemetry_copts() + copts,
      *args,
      **kwargs,
  )
  native.cc_test(
      name = name + "_cpp17",
      deps = deps + ["//3rd_party/catch2:main_lib"],
      copts = opentelemetry_copts() + copts + ["-std=c++17"],
      *args,
      **kwargs,
  )
