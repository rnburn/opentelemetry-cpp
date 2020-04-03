#pragma once

#include <array>
#include <type_traits>

#include "opentelemetry/nostd/detail/void.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace nostd
{
/**
 * Back port of std::add_pointer_t
 */
template< class T >
using add_pointer_t = typename std::add_pointer<T>::type;

/**
 * Back port of std::enable_if_t
 */
template <bool B, class T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

/**
 * Back port of std::remove_const_t
 */
template <typename T>
using remove_const_t = typename std::remove_const<T>::type;

/**
 * Back port of std::remove_reference_t
 */
template <typename T>
using remove_reference_t = typename std::remove_reference<T>::type;

/**
 * Back port of std::remove_cvref_t
 */
template <typename T>
using remove_cvref_t = typename std::remove_cv<remove_reference_t<T>>::type;

/**
 * Back port of std::remove_all_extents
 */
template <typename T>
struct remove_all_extents
{
  using type = T;
};

template <typename T, std::size_t N>
struct remove_all_extents<std::array<T, N>> : remove_all_extents<T>
{};

/**
 * Back port of std::remove_all_extents_t
 */
template <typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

/**
 * Back port of std::is_swappable
 */
namespace detail
{
namespace swappable
{

using std::swap;

template <typename T>
struct is_swappable
{
private:
  template <typename U, typename = decltype(swap(std::declval<U &>(), std::declval<U &>()))>
  inline static std::true_type test(int);

  template <typename U>
  inline static std::false_type test(...);

public:
  static constexpr bool value = decltype(test<T>(0))::value;
};

}  // namespace swappable
}  // namespace detail

using detail::swappable::is_swappable;

/**
 * Back port of std::is_swappable
 */
namespace detail {
namespace swappable {
template <bool IsSwappable, typename T>
struct is_nothrow_swappable
{
  static constexpr bool value = noexcept(swap(std::declval<T &>(), std::declval<T &>()));
};

template <typename T>
struct is_nothrow_swappable<false, T> : std::false_type
{};
} // namespace swappable
} // namespace detail
template <typename T>
using is_nothrow_swappable = detail::swappable::is_nothrow_swappable<is_swappable<T>::value, T>;
}  // namespace nostd
OPENTELEMETRY_END_NAMESPACE
