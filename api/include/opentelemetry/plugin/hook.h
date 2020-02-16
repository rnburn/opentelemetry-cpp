#pragma once

#include "opentelemetry/plugin/factory.h"
#include "opentelemetry/plugin/loader_info.h"

#ifdef WIN32

/**
 * Cross-platform helper macro to declare the symbol used to load an OpenTelemetry implementation
 * as a plugin.
 *
 * Note: The symbols use weak linkage so as to support using an OpenTelemetry both as a regular
 * library and a dynamically loaded plugin. The weak linkage allows for multiple implementations to
 * be linked in without getting multiple definition errors.
 */
#  define OPENTELEMETRY_DEFINE_PLUGIN_HOOK(X)                                            \
    extern "C" {                                                                         \
    extern __declspec(dllexport)                                                         \
        opentelemetry::plugin::OpenTelemetryHook const OpenTelemetryMakeFactoryImpl;     \
                                                                                         \
    __declspec(selectany)                                                                \
        opentelemetry::plugin::OpenTelemetryHook const OpenTelemetryMakeFactoryImpl = X; \
    }  // extern "C"

#else

#  define OPENTELEMETRY_DEFINE_PLUGIN_HOOK(X)                                                      \
    extern "C" {                                                                                   \
    __attribute((                                                                                  \
        weak)) extern opentelemetry::plugin::OpenTelemetryHook const OpenTelemetryMakeFactoryImpl; \
                                                                                                   \
    opentelemetry::plugin::OpenTelemetryHook const OpenTelemetryMakeFactoryImpl = X;               \
    }  // extern "C"

#endif

namespace opentelemetry
{
namespace plugin
{
using OpenTelemetryHook =
    nostd::unique_ptr<Factory::FactoryImpl> (*)(const LoaderInfo &loader_info,
                                                nostd::unique_ptr<char[]> &error_message);
}  // namespace plugin
}  // namespace opentelemetry
