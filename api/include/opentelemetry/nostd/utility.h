#pragma once

#include <cstddef>
#include <initializer_list>

#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace nostd
{
/**
 * Back port of std::data
 *
 * See https://en.cppreference.com/w/cpp/iterator/data
 */
template <class C>
auto data(C &c) noexcept(noexcept(c.data())) -> decltype(c.data())
{
  return c.data();
}

template <class C>
auto data(const C &c) noexcept(noexcept(c.data())) -> decltype(c.data())
{
  return c.data();
}

template <class T, size_t N>
T *data(T (&array)[N]) noexcept
{
  return array;
}

template <class E>
const E *data(std::initializer_list<E> list) noexcept
{
  return list.begin();
}

/**
 * Back port of std::size
 *
 * See https://en.cppreference.com/w/cpp/iterator/size
 */
template <class C>
auto size(const C &c) noexcept(noexcept(c.size())) -> decltype(c.size())
{
  return c.size();
}

template <class T, size_t N>
size_t size(T (&array)[N]) noexcept
{
  return N;
}

/**
 * Back port of std::integer_sequence
 */
template <typename T, T... Is>
struct integer_sequence
{
  using value_type = T;
  static constexpr std::size_t size() noexcept { return sizeof...(Is); }
};

/**
 * Back port of std::index_sequence
 */
template <std::size_t... Is>
using index_sequence = integer_sequence<std::size_t, Is...>;

/**
 * Back port of std::make_index_sequence
 */
namespace detail {
template<class, size_t>
struct index_sequence_push_back {};

template <size_t... Indexes, size_t I>
struct index_sequence_push_back<index_sequence<Indexes...>, I> {
  using type = index_sequence<Indexes..., I>;
};

template <size_t N>
struct make_index_sequence_impl {
  using type = typename index_sequence_push_back<typename make_index_sequence_impl<N - 1>::type,
                                                 N - 1>::type;
};

template <>
struct make_index_sequence_impl<0> {
  using type = index_sequence<>;
};
} // namespace detail

template <size_t N>
using make_index_sequence = typename detail::make_index_sequence_impl<N>::type;

/**
 * Back port of std::index_sequence_for
 */
template <class... Ts>
using index_sequence_for = make_index_sequence<sizeof...(Ts)>;
}  // namespace nostd
OPENTELEMETRY_END_NAMESPACE
