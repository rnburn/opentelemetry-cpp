#pragma once

#ifdef WIN32
#  include "opentelemetry/plugin/detail/dynamic_load_windows.h"
#else
#  include "opentelemetry/plugin/detail/dynamic_load_unix.h"
#endif

namespace opentelemetry
{
namespace plugin
{
/**
 * Load an OpenTelemetry implementation as a plugin.
 * @param plugin the path to the plugin to load
 * @param error_message on failure this is set to an error message
 * @return a Factory that can be used to create OpenTelemetry objects or nullptr on failure.
 */
std::unique_ptr<Factory> LoadFactory(const char *plugin,
                                     std::unique_ptr<char[]> &error_message) noexcept;
}  // namespace plugin
}  // namespace opentelemetry
