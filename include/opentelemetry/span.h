#ifndef OT_TRACER_H
#define OT_TRACER_H

#include <chrono>
#include <initializer_list>
#include <utility>
#include <vector>

#include <opentelemetry/timestamp.h>
#include <opentelemetry/attribute_value.h>

class Tracer;

struct EndSpanOptions {
};

class Span {
 public:
  virtual const Tracer& tracer() const noexcept = 0;

  virtual void SetAttribute(string_view key,
                            const AttributeValue& value) noexcept = 0;

  virtual void AddEvent(string_view name) noexcept = 0;

  virtual void AddEvent(string_view name,
                        const Timestamp& timestamp) noexcept = 0;

  virtual void AddEvent(
      string_view name,
      std::initializer_list<std::pair<string_view, AttributeValue>>
          key_values) noexcept = 0;

  virtual void AddEvent(
      string_view name, const Timestamp& timestamp,
      std::initializer_list<std::pair<string_view, AttributeValue>>
          key_values) noexcept = 0;

  virtual void AddEvent(
      string_view name, const Timestamp& timestamp,
      const std::vector<std::pair<string_view, AttributeValue>>&
          key_values) noexcept = 0;

  virtual void SetName(string_view name) noexcept = 0;

  virtual void End(const EndSpanOptions& options) noexcept = 0;
};

#endif  // OT_TRACER_H
