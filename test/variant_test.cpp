#include "opentelemetry/variant.h"

#include <string>

#include "3rd_party/catch2/catch.hpp"
namespace ot = opentelemetry;

TEST_CASE("variant") {
  ot::variant<std::string, double> v1{"cat"};
  v1 = 1.23;
#if __cplusplus >= 201703L
  // For c++17 and above, ot::variant is the same as std::variant
  REQUIRE(std::is_same_v<ot::variant<int>, std::variant<int>>);
#endif
}
