#include "opentelemetry/attribute_value.h"

#include "3rd_party/catch2/catch.hpp"
namespace ot = opentelemetry;

TEST_CASE("attribute_value") {
  ot::AttributeValue value_string{std::string{"abc"}};
  REQUIRE(ot::get_if<std::string>(&value_string) != nullptr);
  REQUIRE(ot::get<std::string>(value_string) == "abc");

  ot::AttributeValue value_string_view{ot::string_view{"abc"}};
  REQUIRE(ot::get_if<ot::string_view>(&value_string_view) != nullptr);
  REQUIRE((ot::get<ot::string_view>(value_string_view) == "abc"));

  ot::AttributeValue value_cstring{"abc"};
  REQUIRE(ot::get_if<const char*>(&value_cstring) != nullptr);
  REQUIRE(ot::get<const char*>(value_cstring) == std::string{"abc"});

  ot::AttributeValue value_bool{true};
  REQUIRE(ot::get_if<bool>(&value_bool) != nullptr);
  REQUIRE(ot::get<bool>(value_bool));

  ot::AttributeValue value_int{123};
  REQUIRE(ot::get_if<int>(&value_int) != nullptr);
  REQUIRE(ot::get<int>(value_int) == 123);

  ot::AttributeValue value_unsigned_int{123u};
  REQUIRE(ot::get_if<unsigned int>(&value_unsigned_int) != nullptr);
  REQUIRE(ot::get<unsigned int>(value_unsigned_int) == 123u);

  ot::AttributeValue value_long{123l};
  REQUIRE(ot::get_if<long>(&value_long) != nullptr);
  REQUIRE(ot::get<long>(value_long) == 123);

  ot::AttributeValue value_unsigned_long{123ul};
  REQUIRE(ot::get_if<unsigned long>(&value_unsigned_long) != nullptr);
  REQUIRE(ot::get<unsigned long>(value_unsigned_long) == 123ul);

  ot::AttributeValue value_double{1.23};
  REQUIRE(ot::get_if<double>(&value_double) != nullptr);
  REQUIRE(ot::get<double>(value_double) == 1.23);
}
