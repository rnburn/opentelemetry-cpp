#include "opentelemetry/trace/key_value_iterable_view.h"

#include <map>

#include <gtest/gtest.h>

using namespace opentelemetry;

static std::map<std::string, trace::AttributeValue> TakeKeyValues(
    const trace::KeyValueIterable &iterable)
{
  std::map<std::string, trace::AttributeValue> result;
  iterable.ForEachKeyValue([&](nostd::string_view key, trace::AttributeValue value) noexcept {
    result.emplace(key, value);
    return true;
  });
  return result;
}

template <class T,
          nostd::enable_if_t<trace::detail::is_key_value_iterable<T>::value> * = nullptr>
static std::map<std::string, trace::AttributeValue> TakeKeyValues(const T &iterable)
{
  return TakeKeyValues(trace::KeyValueIterableView<T>{iterable});
}

TEST(KeyValueIterableViewTest, is_key_value_iterable) {
  using M1 = std::map<std::string, std::string>;
  EXPECT_TRUE(bool{trace::detail::is_key_value_iterable<M1>::value});

  using M2 = std::map<std::string, int>;
  EXPECT_TRUE(bool{trace::detail::is_key_value_iterable<M2>::value});

  using M3 = std::map<std::string, trace::AttributeValue>;
  EXPECT_TRUE(bool{trace::detail::is_key_value_iterable<M3>::value});

  struct A {};
  using M4 = std::map<std::string, A>;
  EXPECT_FALSE(bool{trace::detail::is_key_value_iterable<M4>::value});
}

TEST(KeyValueIterableViewTest, ForEachKeyValue) {
  std::map<std::string, std::string> m1 = {{"abc", "123"}, {"xyz", "456"}};
  EXPECT_EQ(TakeKeyValues(m1),
            (std::map<std::string, trace::AttributeValue>{{"abc", "123"}, {"xyz", "456"}}));

  std::vector<std::pair<std::string, int>> v1 = {{"abc", 123}, {"xyz", 456}};
  EXPECT_EQ(TakeKeyValues(v1),
            (std::map<std::string, trace::AttributeValue>{{"abc", 123}, {"xyz", 456}}));
}

TEST(KeyValueIterableViewTest, ForEachKeyValueWithExit) {
  using M = std::map<std::string, std::string>;
  M m1 = {{"abc", "123"}, {"xyz", "456"}};
  trace::KeyValueIterableView<M> iterable{m1};
  int count = 0;
  auto exit = iterable.ForEachKeyValue([&count](nostd::string_view /*key*/,
                                                trace::AttributeValue /*value*/) noexcept {
    ++count;
    return false;
  });
  EXPECT_EQ(count, 1);
  EXPECT_FALSE(exit);
}