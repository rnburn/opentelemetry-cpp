#include "opentelemetry/string_view.h"

#include "3rd_party/catch2/catch.hpp"
namespace ot = opentelemetry;

TEST_CASE("string_view") { 
  ot::string_view s = "abc123"; 
  REQUIRE((s == "abc123"));
}
