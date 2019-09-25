#ifndef OT_ATTRIBUTE_VALUE_H
#define OT_ATTRIBUTE_VALUE_H

#include <string>

#include <opentelemetry/variant.h>
#include <opentelemetry/string_view.h>

namespace opentelemetry {

using AttributeValue = variant<std::string, string_view, const char*, bool, int,
                               unsigned int, long, unsigned long, double>;

} // namespace opentelemetry

#endif // OT_ATTRIBUTE_VALUE_H
