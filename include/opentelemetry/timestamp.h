#ifndef OT_TIMESTAMP_H
#define OT_TIMESTAMP_H

#include <chrono>

namespace opentelemetry {
class Timestamp {
 public:
  Timestamp() = default;

  Timestamp(const std::chrono::system_clock::time_point& system_time_point,
            const std::chrono::steady_clock::time_point& steady_time_point) noexcept
      : system_time_point_{system_time_point},
        steady_time_point_{steady_time_point} {}

  /*implicit*/ Timestamp(
      const std::chrono::system_clock::time_point& system_time_point) noexcept
      : system_time_point_{system_time_point} {}

  /*implicit*/ Timestamp(
      const std::chrono::steady_clock::time_point& steady_time_point) noexcept
      : steady_time_point_{steady_time_point} {}

  const std::chrono::system_clock::time_point& systemTimePoint() const
      noexcept {
    return system_time_point_;
  }

  const std::chrono::steady_clock::time_point& steadyTimePoint() const
      noexcept {
    return steady_time_point_;
  }

  bool hasSystemTimePoint() const noexcept {
    return system_time_point_ != std::chrono::system_clock::time_point{};
  }

  bool hasSteadyTimePoint() const noexcept {
    return steady_time_point_ != std::chrono::steady_clock::time_point{};
  }

 private:
  std::chrono::system_clock::time_point system_time_point_;
  std::chrono::steady_clock::time_point steady_time_point_;
};
} // namespace opentelemetry
#endif // OT_TIMESTAMP_H
