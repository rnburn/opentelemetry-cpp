// Copyright 2017-2019 by Martin Moene
//
// string-view lite, a C++17-like string_view for C++98 and later.
// For more information see https://github.com/martinmoene/string-view-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#ifndef NONSTD_SV_LITE_H_INCLUDED
#define NONSTD_SV_LITE_H_INCLUDED

// string-view lite configuration:

#define nssv_STRING_VIEW_DEFAULT  0
#define nssv_STRING_VIEW_NONSTD   1
#define nssv_STRING_VIEW_STD      2

#if !defined( nssv_CONFIG_SELECT_STRING_VIEW )
# define nssv_CONFIG_SELECT_STRING_VIEW  ( nssv_HAVE_STD_STRING_VIEW ? nssv_STRING_VIEW_STD : nssv_STRING_VIEW_NONSTD )
#endif

#if defined( nssv_CONFIG_SELECT_STD_STRING_VIEW ) || defined( nssv_CONFIG_SELECT_NONSTD_STRING_VIEW )
# error nssv_CONFIG_SELECT_STD_STRING_VIEW and nssv_CONFIG_SELECT_NONSTD_STRING_VIEW are deprecated and removed, please use nssv_CONFIG_SELECT_STRING_VIEW=nssv_STRING_VIEW_...
#endif

#ifndef  nssv_CONFIG_STD_SV_OPERATOR
# define nssv_CONFIG_STD_SV_OPERATOR  0
#endif

#ifndef  nssv_CONFIG_USR_SV_OPERATOR
# define nssv_CONFIG_USR_SV_OPERATOR  1
#endif

#ifdef   nssv_CONFIG_CONVERSION_STD_STRING
# define nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS   nssv_CONFIG_CONVERSION_STD_STRING
# define nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS  nssv_CONFIG_CONVERSION_STD_STRING
#endif

#ifndef  nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS
# define nssv_CONFIG_CONVERSION_STD_STRING_CLASS_METHODS  1
#endif

#ifndef  nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS
# define nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS  1
#endif

// Control presence of exception handling (try and auto discover):

#ifndef nssv_CONFIG_NO_EXCEPTIONS
# if defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)
#  define nssv_CONFIG_NO_EXCEPTIONS  0
# else
#  define nssv_CONFIG_NO_EXCEPTIONS  1
# endif
#endif

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   nssv_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define nssv_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define nssv_CPLUSPLUS  __cplusplus
# endif
#endif

#define nssv_CPP98_OR_GREATER  ( nssv_CPLUSPLUS >= 199711L )
#define nssv_CPP11_OR_GREATER  ( nssv_CPLUSPLUS >= 201103L )
#define nssv_CPP11_OR_GREATER_ ( nssv_CPLUSPLUS >= 201103L )
#define nssv_CPP14_OR_GREATER  ( nssv_CPLUSPLUS >= 201402L )
#define nssv_CPP17_OR_GREATER  ( nssv_CPLUSPLUS >= 201703L )
#define nssv_CPP20_OR_GREATER  ( nssv_CPLUSPLUS >= 202000L )

// use C++17 std::string_view if available and requested:

#if nssv_CPP17_OR_GREATER && defined(__has_include )
# if __has_include( <string_view> )
#  define nssv_HAVE_STD_STRING_VIEW  1
# else
#  define nssv_HAVE_STD_STRING_VIEW  0
# endif
#else
# define  nssv_HAVE_STD_STRING_VIEW  0
#endif

#define  nssv_USES_STD_STRING_VIEW  ( (nssv_CONFIG_SELECT_STRING_VIEW == nssv_STRING_VIEW_STD) || ((nssv_CONFIG_SELECT_STRING_VIEW == nssv_STRING_VIEW_DEFAULT) && nssv_HAVE_STD_STRING_VIEW) )

#define nssv_HAVE_STARTS_WITH ( nssv_CPP20_OR_GREATER || !nssv_USES_STD_STRING_VIEW )
#define nssv_HAVE_ENDS_WITH     nssv_HAVE_STARTS_WITH

//
// Use C++17 std::string_view:
//

#if nssv_USES_STD_STRING_VIEW

#include <string_view>

// Extensions for std::string:

#if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS

namespace opentelemetry {

template< class CharT, class Traits, class Allocator = std::allocator<CharT> >
std::basic_string<CharT, Traits, Allocator>
to_string( std::basic_string_view<CharT, Traits> v, Allocator const & a = Allocator() )
{
    return std::basic_string<CharT,Traits, Allocator>( v.begin(), v.end(), a );
}

template< class CharT, class Traits, class Allocator >
std::basic_string_view<CharT, Traits>
to_string_view( std::basic_string<CharT, Traits, Allocator> const & s )
{
    return std::basic_string_view<CharT, Traits>( s.data(), s.size() );
}

} // namespace opentelemetry

#endif // nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS

namespace opentelemetry {

using std::string_view;
using std::wstring_view;
using std::basic_string_view;

// literal "sv" and "_sv", see above

using std::operator==;
using std::operator!=;
using std::operator<;
using std::operator<=;
using std::operator>;
using std::operator>=;

using std::operator<<;

} // namespace opentelemetry

#else // nssv_HAVE_STD_STRING_VIEW

//
// Before C++17: use string_view lite:
//

// Compiler versions:
//
// MSVC++ 6.0  _MSC_VER == 1200 (Visual Studio 6.0)
// MSVC++ 7.0  _MSC_VER == 1300 (Visual Studio .NET 2002)
// MSVC++ 7.1  _MSC_VER == 1310 (Visual Studio .NET 2003)
// MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)
// MSVC++ 9.0  _MSC_VER == 1500 (Visual Studio 2008)
// MSVC++ 10.0 _MSC_VER == 1600 (Visual Studio 2010)
// MSVC++ 11.0 _MSC_VER == 1700 (Visual Studio 2012)
// MSVC++ 12.0 _MSC_VER == 1800 (Visual Studio 2013)
// MSVC++ 14.0 _MSC_VER == 1900 (Visual Studio 2015)
// MSVC++ 14.1 _MSC_VER >= 1910 (Visual Studio 2017)

#if defined(_MSC_VER ) && !defined(__clang__)
# define nssv_COMPILER_MSVC_VER      (_MSC_VER )
# define nssv_COMPILER_MSVC_VERSION  (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define nssv_COMPILER_MSVC_VER      0
# define nssv_COMPILER_MSVC_VERSION  0
#endif

#define nssv_COMPILER_VERSION( major, minor, patch )  ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined(__clang__)
# define nssv_COMPILER_CLANG_VERSION  nssv_COMPILER_VERSION(__clang_major__, __clang_minor__, __clang_patchlevel__)
#else
# define nssv_COMPILER_CLANG_VERSION    0
#endif

#if defined(__GNUC__) && !defined(__clang__)
# define nssv_COMPILER_GNUC_VERSION  nssv_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
# define nssv_COMPILER_GNUC_VERSION    0
#endif

// half-open range [lo..hi):
#define nssv_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Presence of language and library features:

// Unless defined otherwise below, consider VC14 as C++11 for variant-lite:

#if nssv_COMPILER_MSVC_VER >= 1900
# undef  nssv_CPP11_OR_GREATER
# define nssv_CPP11_OR_GREATER  1
#endif

#define nssv_CPP11_90   (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1500)
#define nssv_CPP11_100  (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1600)
#define nssv_CPP11_110  (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1700)
#define nssv_CPP11_120  (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1800)
#define nssv_CPP11_140  (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1900)
#define nssv_CPP11_141  (nssv_CPP11_OR_GREATER_ || nssv_COMPILER_MSVC_VER >= 1910)

#define nssv_CPP14_000  (nssv_CPP14_OR_GREATER)
#define nssv_CPP17_000  (nssv_CPP17_OR_GREATER)

// Presence of C++17 language features:

#define nssv_HAVE_NODISCARD             nssv_CPP17_000

// Presence of C++ library features:

#define nssv_HAVE_STD_HASH              nssv_CPP11_120

// C++ feature usage:

// Additional includes:

#include <algorithm>
#include <cassert>
#include <iterator>
#include <limits>
#include <ostream>
#include <string>   // std::char_traits<>

#if ! nssv_CONFIG_NO_EXCEPTIONS
# include <stdexcept>
#endif

#if nssv_CPP11_OR_GREATER
# include <type_traits>
#endif

// Clang, GNUC, MSVC warning suppression macros:

#if defined(__clang__)
# pragma clang diagnostic ignored "-Wreserved-user-defined-literal"
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wuser-defined-literals"
#elif defined(__GNUC__)
# pragma  GCC  diagnostic push
# pragma  GCC  diagnostic ignored "-Wliteral-suffix"
#endif // __clang__

#if nssv_COMPILER_MSVC_VERSION >= 140
# define nssv_SUPPRESS_MSGSL_WARNING(expr)        [[gsl::suppress(expr)]]
# define nssv_SUPPRESS_MSVC_WARNING(code, descr)  __pragma(warning(suppress: code) )
# define nssv_DISABLE_MSVC_WARNINGS(codes)        __pragma(warning(push))  __pragma(warning(disable: codes))
#else
# define nssv_SUPPRESS_MSGSL_WARNING(expr)
# define nssv_SUPPRESS_MSVC_WARNING(code, descr)
# define nssv_DISABLE_MSVC_WARNINGS(codes)
#endif

#if defined(__clang__)
# define nssv_RESTORE_WARNINGS()  _Pragma("clang diagnostic pop")
#elif defined(__GNUC__)
# define nssv_RESTORE_WARNINGS()  _Pragma("GCC diagnostic pop")
#elif nssv_COMPILER_MSVC_VERSION >= 140
# define nssv_RESTORE_WARNINGS()  __pragma(warning(pop ))
#else
# define nssv_RESTORE_WARNINGS()
#endif

// Suppress the following MSVC (GSL) warnings:
// - C4455, non-gsl   : 'operator ""sv': literal suffix identifiers that do not
//                      start with an underscore are reserved
// - C26472, gsl::t.1 : don't use a static_cast for arithmetic conversions;
//                      use brace initialization, gsl::narrow_cast or gsl::narow
// - C26481: gsl::b.1 : don't use pointer arithmetic. Use span instead

nssv_DISABLE_MSVC_WARNINGS( 4455 26481 26472 )
//nssv_DISABLE_CLANG_WARNINGS( "-Wuser-defined-literals" )
//nssv_DISABLE_GNUC_WARNINGS( -Wliteral-suffix )

namespace opentelemetry { namespace sv_lite {

template
<
    class CharT,
    class Traits = std::char_traits<CharT>
>
class basic_string_view;

//
// basic_string_view:
//

template
<
    class CharT,
    class Traits /* = std::char_traits<CharT> */
>
class basic_string_view
{
public:
    // Member types:

    typedef Traits traits_type;
    typedef CharT  value_type;

    typedef CharT       * pointer;
    typedef CharT const * const_pointer;
    typedef CharT       & reference;
    typedef CharT const & const_reference;

    typedef const_pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator< const_iterator > reverse_iterator;
    typedef	std::reverse_iterator< const_iterator > const_reverse_iterator;

    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    // 24.4.2.1 Construction and assignment:

    basic_string_view() noexcept
        : data_( nullptr )
        , size_( 0 )
    {}

    basic_string_view( basic_string_view const & other ) noexcept = default;

    basic_string_view( CharT const * s, size_type count ) noexcept // non-standard noexcept
        : data_( s )
        , size_( count )
    {}

    basic_string_view( CharT const * s) noexcept // non-standard noexcept
        : data_( s )
        , size_( Traits::length(s) )
    {}

    // Assignment:

    basic_string_view & operator=( basic_string_view const & other ) noexcept = default;

    // 24.4.2.2 Iterator support:

    const_iterator begin()  const noexcept { return data_;         }
    const_iterator end()    const noexcept { return data_ + size_; }

    const_iterator cbegin() const noexcept { return begin(); }
    const_iterator cend()   const noexcept { return end();   }

    const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator( end() );   }
    const_reverse_iterator rend()    const noexcept { return const_reverse_iterator( begin() ); }

    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    const_reverse_iterator crend()   const noexcept { return rend();   }

    // 24.4.2.3 Capacity:

    size_type size()     const noexcept { return size_; }
    size_type length()   const noexcept { return size_; }
    size_type max_size() const noexcept { return (std::numeric_limits< size_type >::max)(); }

    // since C++20
    bool empty() const noexcept
    {
        return 0 == size_;
    }

    // 24.4.2.4 Element access:

    const_reference operator[]( size_type pos ) const
    {
        return data_at( pos );
    }

    const_reference at( size_type pos ) const
    {
#if nssv_CONFIG_NO_EXCEPTIONS
        assert( pos < size() );
#else
        if ( pos >= size() )
        {
            throw std::out_of_range("opentelemetry::string_view::at()");
        }
#endif
        return data_at( pos );
    }

    const_reference front() const { return data_at( 0 );          }
    const_reference back()  const { return data_at( size() - 1 ); }

    const_pointer   data()  const noexcept { return data_; }

    // 24.4.2.5 Modifiers:

    void remove_prefix( size_type n )
    {
        assert( n <= size() );
        data_ += n;
        size_ -= n;
    }

    void remove_suffix( size_type n )
    {
        assert( n <= size() );
        size_ -= n;
    }

    void swap( basic_string_view & other ) noexcept
    {
        using std::swap;
        swap( data_, other.data_ );
        swap( size_, other.size_ );
    }

    // 24.4.2.6 String operations:

    size_type copy( CharT * dest, size_type n, size_type pos = 0 ) const
    {
#if nssv_CONFIG_NO_EXCEPTIONS
        assert( pos <= size() );
#else
        if ( pos > size() )
        {
            throw std::out_of_range("opentelemetry::string_view::copy()");
        }
#endif
        const size_type rlen = (std::min)( n, size() - pos );

        (void) Traits::copy( dest, data() + pos, rlen );

        return rlen;
    }

    basic_string_view substr( size_type pos = 0, size_type n = npos ) const
    {
#if nssv_CONFIG_NO_EXCEPTIONS
        assert( pos <= size() );
#else
        if ( pos > size() )
        {
            throw std::out_of_range("opentelemetry::string_view::substr()");
        }
#endif
        return basic_string_view( data() + pos, (std::min)( n, size() - pos ) );
    }

    // compare(), 6x:

    int compare( basic_string_view other ) const noexcept // (1)
    {
        if ( const int result = Traits::compare( data(), other.data(), (std::min)( size(), other.size() ) ) )
        {
            return result;
        }

        return size() == other.size() ? 0 : size() < other.size() ? -1 : 1;
    }

    int compare( size_type pos1, size_type n1, basic_string_view other ) const // (2)
    {
        return substr( pos1, n1 ).compare( other );
    }

    int compare( size_type pos1, size_type n1, basic_string_view other, size_type pos2, size_type n2 ) const // (3)
    {
        return substr( pos1, n1 ).compare( other.substr( pos2, n2 ) );
    }

    int compare( CharT const * s ) const // (4)
    {
        return compare( basic_string_view( s ) );
    }

    int compare( size_type pos1, size_type n1, CharT const * s ) const // (5)
    {
        return substr( pos1, n1 ).compare( basic_string_view( s ) );
    }

    int compare( size_type pos1, size_type n1, CharT const * s, size_type n2 ) const // (6)
    {
        return substr( pos1, n1 ).compare( basic_string_view( s, n2 ) );
    }

    // 24.4.2.7 Searching:

    // starts_with(), 3x, since C++20:

    bool starts_with( basic_string_view v ) const noexcept  // (1)
    {
        return size() >= v.size() && compare( 0, v.size(), v ) == 0;
    }

    bool starts_with( CharT c ) const noexcept  // (2)
    {
        return starts_with( basic_string_view( &c, 1 ) );
    }

    bool starts_with( CharT const * s ) const  // (3)
    {
        return starts_with( basic_string_view( s ) );
    }

    // ends_with(), 3x, since C++20:

    bool ends_with( basic_string_view v ) const noexcept  // (1)
    {
        return size() >= v.size() && compare( size() - v.size(), npos, v ) == 0;
    }

    bool ends_with( CharT c ) const noexcept  // (2)
    {
        return ends_with( basic_string_view( &c, 1 ) );
    }

    bool ends_with( CharT const * s ) const  // (3)
    {
        return ends_with( basic_string_view( s ) );
    }

    // find(), 4x:

    size_type find( basic_string_view v, size_type pos = 0 ) const noexcept  // (1)
    {
        return assert( v.size() == 0 || v.data() != nullptr )
            , pos >= size()
            ? npos
            : to_pos( std::search( cbegin() + pos, cend(), v.cbegin(), v.cend(), Traits::eq ) );
    }

    size_type find( CharT c, size_type pos = 0 ) const noexcept  // (2)
    {
        return find( basic_string_view( &c, 1 ), pos );
    }

    size_type find( CharT const * s, size_type pos, size_type n ) const  // (3)
    {
        return find( basic_string_view( s, n ), pos );
    }

    size_type find( CharT const * s, size_type pos = 0 ) const  // (4)
    {
        return find( basic_string_view( s ), pos );
    }

    // rfind(), 4x:

    size_type rfind( basic_string_view v, size_type pos = npos ) const noexcept  // (1)
    {
        if ( size() < v.size() )
        {
            return npos;
        }

        if ( v.empty() )
        {
            return (std::min)( size(), pos );
        }

        const_iterator last   = cbegin() + (std::min)( size() - v.size(), pos ) + v.size();
        const_iterator result = std::find_end( cbegin(), last, v.cbegin(), v.cend(), Traits::eq );

        return result != last ? size_type( result - cbegin() ) : npos;
    }

    size_type rfind( CharT c, size_type pos = npos ) const noexcept  // (2)
    {
        return rfind( basic_string_view( &c, 1 ), pos );
    }

    size_type rfind( CharT const * s, size_type pos, size_type n ) const  // (3)
    {
        return rfind( basic_string_view( s, n ), pos );
    }

    size_type rfind( CharT const * s, size_type pos = npos ) const  // (4)
    {
        return rfind( basic_string_view( s ), pos );
    }

    // find_first_of(), 4x:

    size_type find_first_of( basic_string_view v, size_type pos = 0 ) const noexcept  // (1)
    {
        return pos >= size()
            ? npos
            : to_pos( std::find_first_of( cbegin() + pos, cend(), v.cbegin(), v.cend(), Traits::eq ) );
    }

    size_type find_first_of( CharT c, size_type pos = 0 ) const noexcept  // (2)
    {
        return find_first_of( basic_string_view( &c, 1 ), pos );
    }

    size_type find_first_of( CharT const * s, size_type pos, size_type n ) const  // (3)
    {
        return find_first_of( basic_string_view( s, n ), pos );
    }

    size_type find_first_of(  CharT const * s, size_type pos = 0 ) const  // (4)
    {
        return find_first_of( basic_string_view( s ), pos );
    }

    // find_last_of(), 4x:

    size_type find_last_of( basic_string_view v, size_type pos = npos ) const noexcept  // (1)
    {
        return empty()
            ? npos
            : pos >= size()
            ? find_last_of( v, size() - 1 )
            : to_pos( std::find_first_of( const_reverse_iterator( cbegin() + pos + 1 ), crend(), v.cbegin(), v.cend(), Traits::eq ) );
    }

    size_type find_last_of( CharT c, size_type pos = npos ) const noexcept  // (2)
    {
        return find_last_of( basic_string_view( &c, 1 ), pos );
    }

    size_type find_last_of( CharT const * s, size_type pos, size_type count ) const  // (3)
    {
        return find_last_of( basic_string_view( s, count ), pos );
    }

    size_type find_last_of( CharT const * s, size_type pos = npos ) const  // (4)
    {
        return find_last_of( basic_string_view( s ), pos );
    }

    // find_first_not_of(), 4x:

    size_type find_first_not_of( basic_string_view v, size_type pos = 0 ) const noexcept  // (1)
    {
        return pos >= size()
            ? npos
            : to_pos( std::find_if( cbegin() + pos, cend(), not_in_view( v ) ) );
    }

    size_type find_first_not_of( CharT c, size_type pos = 0 ) const noexcept  // (2)
    {
        return find_first_not_of( basic_string_view( &c, 1 ), pos );
    }

    size_type find_first_not_of( CharT const * s, size_type pos, size_type count ) const  // (3)
    {
        return find_first_not_of( basic_string_view( s, count ), pos );
    }

    size_type find_first_not_of( CharT const * s, size_type pos = 0 ) const  // (4)
    {
        return find_first_not_of( basic_string_view( s ), pos );
    }

    // find_last_not_of(), 4x:

    size_type find_last_not_of( basic_string_view v, size_type pos = npos ) const noexcept  // (1)
    {
        return empty()
            ? npos
            : pos >= size()
            ? find_last_not_of( v, size() - 1 )
            : to_pos( std::find_if( const_reverse_iterator( cbegin() + pos + 1 ), crend(), not_in_view( v ) ) );
    }

    size_type find_last_not_of( CharT c, size_type pos = npos ) const noexcept  // (2)
    {
        return find_last_not_of( basic_string_view( &c, 1 ), pos );
    }

    size_type find_last_not_of( CharT const * s, size_type pos, size_type count ) const  // (3)
    {
        return find_last_not_of( basic_string_view( s, count ), pos );
    }

    size_type find_last_not_of( CharT const * s, size_type pos = npos ) const  // (4)
    {
        return find_last_not_of( basic_string_view( s ), pos );
    }

    // Constants:

    enum : size_type { npos = size_type(-1) };

private:
    struct not_in_view
    {
        const basic_string_view v;

        explicit not_in_view( basic_string_view v ) : v( v ) {}

        bool operator()( CharT c ) const
        {
            return npos == v.find_first_of( c );
        }
    };

    size_type to_pos( const_iterator it ) const
    {
        return it == cend() ? npos : size_type( it - cbegin() );
    }

    size_type to_pos( const_reverse_iterator it ) const
    {
        return it == crend() ? npos : size_type( crend() - it - 1 );
    }

    const_reference data_at( size_type pos ) const
    {
        return data_[pos];
    }

private:
    const_pointer data_;
    size_type     size_;

public:

    template< class Allocator >
    basic_string_view( std::basic_string<CharT, Traits, Allocator> const & s ) noexcept
        : data_( s.data() )
        , size_( s.size() )
    {}

    template< class Allocator >
    explicit operator std::basic_string<CharT, Traits, Allocator>() const
    {
        return to_string( Allocator() );
    }

    template< class Allocator = std::allocator<CharT> >
    std::basic_string<CharT, Traits, Allocator>
    to_string( Allocator const & a = Allocator() ) const
    {
        return std::basic_string<CharT, Traits, Allocator>( begin(), end(), a );
    }

};

//
// Non-member functions:
//

// 24.4.3 Non-member comparison functions:
// lexicographically compare two string views (function template):

template< class CharT, class Traits >
bool operator== (
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) noexcept
{ return lhs.compare( rhs ) == 0 ; }

template< class CharT, class Traits >
bool operator!= (
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) noexcept
{ return lhs.compare( rhs ) != 0 ; }

template< class CharT, class Traits >
bool operator< (
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) noexcept
{ return lhs.compare( rhs ) < 0 ; }

template< class CharT, class Traits >
bool operator<= (
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) noexcept
{ return lhs.compare( rhs ) <= 0 ; }

template< class CharT, class Traits >
bool operator> (
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) noexcept
{ return lhs.compare( rhs ) > 0 ; }

template< class CharT, class Traits >
bool operator>= (
    basic_string_view <CharT, Traits> lhs,
    basic_string_view <CharT, Traits> rhs ) noexcept
{ return lhs.compare( rhs ) >= 0 ; }

// Let S be basic_string_view<CharT, Traits>, and sv be an instance of S.
// Implementations shall provide sufficient additional overloads marked
// constexpr and noexcept so that an object t with an implicit conversion
// to S can be compared according to Table 67.

#if nssv_CPP11_OR_GREATER && ! nssv_BETWEEN( nssv_COMPILER_MSVC_VERSION, 100, 141 )

#define nssv_BASIC_STRING_VIEW_I(T,U)  typename std::decay< basic_string_view<T,U> >::type

#if nssv_BETWEEN( nssv_COMPILER_MSVC_VERSION, 140, 150 )
# define nssv_MSVC_ORDER(x)  , int=x
#else
# define nssv_MSVC_ORDER(x)  /*, int=x*/
#endif

// ==

template< class CharT, class Traits  nssv_MSVC_ORDER(1) >
bool operator==(
         basic_string_view  <CharT, Traits> lhs,
    nssv_BASIC_STRING_VIEW_I(CharT, Traits) rhs ) noexcept
{ return lhs.compare( rhs ) == 0; }

template< class CharT, class Traits  nssv_MSVC_ORDER(2) >
bool operator==(
    nssv_BASIC_STRING_VIEW_I(CharT, Traits) lhs,
         basic_string_view  <CharT, Traits> rhs ) noexcept
{ return lhs.size() == rhs.size() && lhs.compare( rhs ) == 0; }

// !=

template< class CharT, class Traits  nssv_MSVC_ORDER(1) >
bool operator!= (
         basic_string_view  < CharT, Traits > lhs,
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) rhs ) noexcept
{ return lhs.size() != rhs.size() || lhs.compare( rhs ) != 0 ; }

template< class CharT, class Traits  nssv_MSVC_ORDER(2) >
bool operator!= (
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) lhs,
         basic_string_view  < CharT, Traits > rhs ) noexcept
{ return lhs.compare( rhs ) != 0 ; }

// <

template< class CharT, class Traits  nssv_MSVC_ORDER(1) >
bool operator< (
         basic_string_view  < CharT, Traits > lhs,
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) rhs ) noexcept
{ return lhs.compare( rhs ) < 0 ; }

template< class CharT, class Traits  nssv_MSVC_ORDER(2) >
bool operator< (
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) lhs,
         basic_string_view  < CharT, Traits > rhs ) noexcept
{ return lhs.compare( rhs ) < 0 ; }

// <=

template< class CharT, class Traits  nssv_MSVC_ORDER(1) >
bool operator<= (
         basic_string_view  < CharT, Traits > lhs,
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) rhs ) noexcept
{ return lhs.compare( rhs ) <= 0 ; }

template< class CharT, class Traits  nssv_MSVC_ORDER(2) >
bool operator<= (
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) lhs,
         basic_string_view  < CharT, Traits > rhs ) noexcept
{ return lhs.compare( rhs ) <= 0 ; }

// >

template< class CharT, class Traits  nssv_MSVC_ORDER(1) >
bool operator> (
         basic_string_view  < CharT, Traits > lhs,
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) rhs ) noexcept
{ return lhs.compare( rhs ) > 0 ; }

template< class CharT, class Traits  nssv_MSVC_ORDER(2) >
bool operator> (
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) lhs,
         basic_string_view  < CharT, Traits > rhs ) noexcept
{ return lhs.compare( rhs ) > 0 ; }

// >=

template< class CharT, class Traits  nssv_MSVC_ORDER(1) >
bool operator>= (
         basic_string_view  < CharT, Traits > lhs,
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) rhs ) noexcept
{ return lhs.compare( rhs ) >= 0 ; }

template< class CharT, class Traits  nssv_MSVC_ORDER(2) >
bool operator>= (
    nssv_BASIC_STRING_VIEW_I( CharT, Traits ) lhs,
         basic_string_view  < CharT, Traits > rhs ) noexcept
{ return lhs.compare( rhs ) >= 0 ; }

#undef nssv_MSVC_ORDER
#undef nssv_BASIC_STRING_VIEW_I

#endif // nssv_CPP11_OR_GREATER

// 24.4.4 Inserters and extractors:

namespace detail {

template< class Stream >
void write_padding( Stream & os, std::streamsize n )
{
    for ( std::streamsize i = 0; i < n; ++i )
        os.rdbuf()->sputc( os.fill() );
}

template< class Stream, class View >
Stream & write_to_stream( Stream & os, View const & sv )
{
    typename Stream::sentry sentry( os );

    if ( !os )
        return os;

    const std::streamsize length = static_cast<std::streamsize>( sv.length() );

    // Whether, and how, to pad:
    const bool      pad = ( length < os.width() );
    const bool left_pad = pad && ( os.flags() & std::ios_base::adjustfield ) == std::ios_base::right;

    if ( left_pad )
        write_padding( os, os.width() - length );

    // Write span characters:
    os.rdbuf()->sputn( sv.begin(), length );

    if ( pad && !left_pad )
        write_padding( os, os.width() - length );

    // Reset output stream width:
    os.width( 0 );

    return os;
}

} // namespace detail

template< class CharT, class Traits >
std::basic_ostream<CharT, Traits> &
operator<<(
    std::basic_ostream<CharT, Traits>& os,
    basic_string_view <CharT, Traits> sv )
{
    return detail::write_to_stream( os, sv );
}

// Several typedefs for common character types are provided:

typedef basic_string_view<char>      string_view;
typedef basic_string_view<wchar_t>   wstring_view;

}} // namespace opentelemetry::sv_lite

//
// Extensions for std::string:
//

#if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS

namespace opentelemetry {
namespace sv_lite {

template< class CharT, class Traits >
std::basic_string<CharT, Traits>
to_string( basic_string_view<CharT, Traits> v )
{
    return std::basic_string<CharT, Traits>( v.begin(), v.end() );
}

template< class CharT, class Traits, class Allocator >
std::basic_string<CharT, Traits, Allocator>
to_string( basic_string_view<CharT, Traits> v, Allocator const & a )
{
    return std::basic_string<CharT, Traits, Allocator>( v.begin(), v.end(), a );
}

template< class CharT, class Traits, class Allocator >
basic_string_view<CharT, Traits>
to_string_view( std::basic_string<CharT, Traits, Allocator> const & s )
{
    return basic_string_view<CharT, Traits>( s.data(), s.size() );
}

}} // namespace opentelemetry::sv_lite

#endif // nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS

//
// make types and algorithms available in namespace opentelemetry:
//

namespace opentelemetry {

using sv_lite::basic_string_view;
using sv_lite::string_view;
using sv_lite::wstring_view;

using sv_lite::operator==;
using sv_lite::operator!=;
using sv_lite::operator<;
using sv_lite::operator<=;
using sv_lite::operator>;
using sv_lite::operator>=;

using sv_lite::operator<<;

#if nssv_CONFIG_CONVERSION_STD_STRING_FREE_FUNCTIONS
using sv_lite::to_string;
using sv_lite::to_string_view;
#endif

} // namespace opentelemetry

// 24.4.5 Hash support (C++11):

// Note: The hash value of a string view object is equal to the hash value of
// the corresponding string object.

#if nssv_HAVE_STD_HASH

#include <functional>

namespace std {

template<>
struct hash< opentelemetry::string_view >
{
public:
    std::size_t operator()( opentelemetry::string_view v ) const noexcept
    {
        return std::hash<std::string>()( std::string( v.data(), v.size() ) );
    }
};

template<>
struct hash< opentelemetry::wstring_view >
{
public:
    std::size_t operator()( opentelemetry::wstring_view v ) const noexcept
    {
        return std::hash<std::wstring>()( std::wstring( v.data(), v.size() ) );
    }
};

} // namespace std

#endif // nssv_HAVE_STD_HASH

nssv_RESTORE_WARNINGS()

#endif // nssv_HAVE_STD_STRING_VIEW
#endif // NONSTD_SV_LITE_H_INCLUDED
