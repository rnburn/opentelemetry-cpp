project(opentelemetry-cpp)

# ==============================================================================
# Version information

# Increment ABI version for any ABI-breaking change.
#
# Also, whenever the ABI is between versions and in development
# suffix the ABI version number with "_unstable".
set(OPENTELEMETRY_ABI_VERSION "3")

# Version number follows semver
# See https://semver.org/
set(OPENTELEMETRY_VERSION_MAJOR "1")
set(OPENTELEMETRY_VERSION_MINOR "6")
set(OPENTELEMETRY_VERSION_PATCH "0")
set(OPENTELEMETRY_VERSION_STRING
  "${OPENTELEMETRY_VERSION_MAJOR}.${OPENTELEMETRY_VERSION_MINOR}.${OPENTELEMETRY_VERSION_PATCH}")

include_directories(include)
include_directories(SYSTEM 3rd_party/mpark/include)
