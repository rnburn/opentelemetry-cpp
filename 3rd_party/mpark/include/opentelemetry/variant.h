#ifndef OPENTELEMETRY_VARIANT
#define OPENTELEMETRY_VARIANT

#include "opentelemetry/detail/config.h"

#ifdef OPENTELEMETRY_HAVE_STD_VARIANT

#include <variant>

namespace opentelemetry {
using std::bad_variant_access;
using std::get;
using std::get_if;
using std::holds_alternative;
using std::monostate;
using std::variant;
using std::variant_alternative;
using std::variant_alternative_t;
using std::variant_npos;
using std::variant_size;
using std::variant_size_v;
using std::visit;
}  // namespace opentelemetry

#else // OPENTELEMETRY_HAVE_STD_VARIANT

#include "opentelemetry/detail/variant_impl.h"

#endif // OPENTELEMETRY_HAVE_STD_VARIANT

#endif // OPENTELEMETRY_VARIANT
