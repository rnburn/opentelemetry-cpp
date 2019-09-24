#ifndef CONFIG_H
#define CONFIG_H

// macOS 10.13 and iOS 10.11 don't let you use <any>, <optional>, or <variant>
// even though the headers exist and are publicly noted to work.  See
// https://github.com/abseil/abseil-cpp/issues/207 and
// https://developer.apple.com/documentation/xcode_release_notes/xcode_10_release_notes
// libc++ spells out the availability requirements in the file
// llvm-project/libcxx/include/__config via the #define
// _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS.
#if defined(__APPLE__) && defined(_LIBCPP_VERSION) && \
  ((defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__) && \
   __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__ < 101400) || \
  (defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) && \
   __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ < 120000) || \
  (defined(__ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__) && \
   __ENVIRONMENT_WATCH_OS_VERSION_MIN_REQUIRED__ < 120000) || \
  (defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__) && \
   __ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__ < 50000))
#define OPENTELEMETRY_INTERNAL_APPLE_CXX17_TYPES_UNAVAILABLE 1
#else
#define OPENTELEMETRY_INTERNAL_APPLE_CXX17_TYPES_UNAVAILABLE 0
#endif

// OPENTELEMETRY_HAVE_STD_VARIANT
//
// Checks whether C++17 std::variant is available.
#ifdef OPENTELEMETRY_HAVE_STD_VARIANT
#error "OPENTELEMETRY_HAVE_STD_VARIANT cannot be directly set."
#endif

#ifdef __has_include
#if __has_include(<variant>) && __cplusplus >= 201703L && \
    !OPENTELEMETRY_INTERNAL_APPLE_CXX17_TYPES_UNAVAILABLE
#define OPENTELEMETRY_HAVE_STD_VARIANT 1
#endif
#endif

#endif // CONFIG_H
