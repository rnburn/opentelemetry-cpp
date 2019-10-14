#include "opentelemetry/timestamp.h"

#include "3rd_party/catch2/catch.hpp"
namespace ot = opentelemetry;

TEST_CASE("timestamp") {
  auto system_time_point = std::chrono::system_clock::now();
  auto steady_time_point = std::chrono::steady_clock::now();
  ot::Timestamp timestamp;
  ot::Timestamp system_timestamp{system_time_point};
  ot::Timestamp steady_timestamp{steady_time_point};
  ot::Timestamp system_steady_timestamp{system_time_point, steady_time_point};

  REQUIRE(!timestamp.hasSteadyTimePoint());
  REQUIRE(!timestamp.hasSystemTimePoint());

  REQUIRE(system_timestamp.hasSystemTimePoint());
  REQUIRE(system_timestamp.systemTimePoint() == system_time_point);

  REQUIRE(steady_timestamp.hasSteadyTimePoint());
  REQUIRE(steady_timestamp.steadyTimePoint() == steady_time_point);

  SECTION("timestamp supports implicit conversion from system timepoints") {
    timestamp = system_time_point;
    REQUIRE(timestamp.hasSystemTimePoint());
    REQUIRE(timestamp.systemTimePoint() == system_time_point);
  }

  SECTION("timestamp supports implicit conversion from steady timepoints") {
    timestamp = steady_time_point;
    REQUIRE(timestamp.hasSteadyTimePoint());
    REQUIRE(timestamp.steadyTimePoint() == steady_time_point);
  }
}
