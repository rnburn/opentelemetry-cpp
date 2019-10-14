#ifndef OT_TRACER_H
#define OT_TRACER_H

#include <memory>

#include <opentelemetry/string_view.h>

namespace opentelemetry {
class Span;

struct StartSpanOptions {
};

class Tracer {
 public:
  virtual std::unique_ptr<Span> StartSpan(string_view name,
                                          const StartSpanOptions& options) const
      noexcept = 0;
};
} // namespace opentelemetry

#endif // OT_TRACER_H
