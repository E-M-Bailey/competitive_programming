// Author: Evan Bailey

// preprocessor flags
#define GCC 0
#define CLANG 1
#define MSVC 2
#define ICC 3 // Not supported

#if defined(__clang__)
#define COMPILER CLANG
#elif defined(__GNUC__)
#define COMPILER GCC
#elif defined(__INTEL_COMPILER)
#define COMPILER ICC
#elif defined(_MSC_VER)
#define COMPILER MSVC
#endif

#ifndef COMPILER
#error "Unknown Compiler"
#elif COMPILER == ICC
#error "ICC not supported"
#endif

#if COMPILER == GCC || COMPILER == CLANG
#define VERSION __cplusplus
#elif COMPILER == MSVC
#define VERSION _MSVC_LANG
#endif

#define CPP_98 (VERSION >= 199711L)
#define CPP_11 (VERSION >= 201103L)
#define CPP_14 (VERSION >= 201402L)
#define CPP_17 (VERSION >= 201703L)
#define CPP_20 (VERSION >= 202002L)
#define CPP_23 (VERSION >= 202302L)

#if !CPP_11
#error "C++ standard before C++11"
#endif

// optimization/target pragmas
#if !DEBUG
#if COMPILER == GCC
#pragma GCC optimize("O3,unroll-loops")
#elif COMPILER == CLANG // TODO
#elif COMPILER == MSVC // TODO
#endif
#endif

#if COMPILER == GCC
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#elif COMPILER == CLANG
#pragma clang attribute push([[gnu::target("avx2,bmi,bmi2,lzcnt,popcnt")]], apply_to = function)
#elif COMPILER == MSVC // TODO
#endif

// attributes and modifiers
#if COMPILER == GCC
#define finline [[gnu::always_inline]]
#elif COMPILER == CLANG
#define finline [[clang::always_inline]]
#elif COMPILER == MSVC
#define finline [[msvc::force_inline]]
#endif

#if CPP_20
#define CNODISCARD [[nodiscard]]
#else
#define CNODISCARD
#endif

#if CPP_17
#define NODISCARD [[nodiscard]]
#define MAYBE_UNUSED [[maybe_unused]]
#else
#define NODISCARD
#define MAYBE_UNUSED
#endif

// conditional modifiers
#if CPP20
#define CONSTEXPR20 constexpr
#else
#define CONSTEXPR20
#endif
#if CPP17
#define CONSTEXPR17 constexpr
#else
#define CONSTEXPR17
#endif
#if CPP14
#define CONSTEXPR14 constexpr
#else
#define CONSTEXPR14
#endif
#if CPP11
#define CONSTEXPR11 constexpr
#else
#define CONSTEXPR11
#endif

// STL headers
// TODO remove redundancies
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if CPP_11
#include <cstdint>

#include <array>
#include <chrono>
#include <forward_list>
#include <initializer_list>
#include <random>
#include <ratio>
#include <scoped_allocator>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#endif

#if CPP_17
#include <optional>
#include <string_view>
#include <variant>
#endif

#if CPP_20
#include <bit>
#include <numbers>
#include <ranges>
#include <span>
#endif

// STL feature backports
#if !CPP_20
// TODO bit
namespace numbers
{
// TODO numbers

};
// TODO span
#endif
// - size, ssize
#if CPP_17
using std::size;
#else
template<typename C>
static constexpr auto size(C const &c) -> decltype(c.size()) { return c.size(); }
template<typename T, std::size_t N>
static constexpr std::size_t size(T const (&)[N]) noexcept { return N; }
#endif
#if CPP_20
using std::ssize;
#else
template<typename C>
static constexpr auto ssize(C const &c) ->
typename std::common_type<std::ptrdiff_t, typename std::make_signed<decltype(c.size())>::type>::type
{
	return c.size();
}
template<typename T, std::ptrdiff_t N>
static constexpr std::ptrdiff_t ssize(T const (&)[N]) noexcept { return N; }
#endif
// - dynamic_extent
#if CPP_20
using std::dynamic_extent;
#else
constexpr std::size_t dynamic_extent = std::numeric_limits<std::size_t>::max();
#endif
// - index_sequence
#if CPP_14
using std::integer_sequence;
using std::index_sequence;
using std::make_integer_sequence;
using std::make_index_sequence;
using std::index_sequence_for;
#else
template<typename T, T ...Is>
struct integer_sequence
{
	static constexpr std::size_t size() noexcept
	{
		return sizeof...(Is);
	}
};
template<std::size_t ...Is>
using index_sequence = integer_sequence<std::size_t, Is...>;
template<typename T, typename U>
struct integer_sequence_cat_impl;
template<typename T, T ...Is, T ...Js>
struct integer_sequence_cat_impl<integer_sequence<T, Is...>, integer_sequence<T, Js...>>
{
	typedef integer_sequence<T, Is..., Js...> type;
};
template<typename T, typename U>
struct make_integer_sequence_impl {};
template<typename T, T N>
struct make_integer_sequence_impl<T, std::integral_constant<T, N>>
{
	typedef typename make_integer_sequence_impl<T, std::integral_constant<T, N - 1>>::type rec;
	typedef typename integer_sequence_cat_impl<rec, integer_sequence<T, N - 1>>::type type;
};
template<typename T>
struct make_integer_sequence_impl<T, std::integral_constant<T, 0>>
{
	typedef integer_sequence<T> type;
};
template<typename T, T N>
using make_integer_sequence = typename make_integer_sequence_impl<T, std::integral_constant<T, N>>::type;
template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;
template<typename ...Ts>
using index_sequence_for = make_index_sequence<sizeof...(Ts)>;
#endif

// testcase control flow exceptions
struct tc_break {};
struct tc_continue {};

// https://stackoverflow.com/questions/76657656/how-can-i-deduce-function-template-arguments-of-type-stdbitsetnreference#comment135152626_76657656
template<std::size_t N>
struct bitset_ref
{
	typedef std::bitset<N> bitset_type;
	typedef typename bitset_type::reference ref_type;
	mutable ref_type ref;

	// std::bitset::reference compatibility
	constexpr bitset_ref(ref_type reference) noexcept : ref(reference) {}
	constexpr bitset_ref(bitset_ref const &) noexcept = default;
	CONSTEXPR14 bitset_ref operator=(bool x) const noexcept { ref = x; return *this; }
	CONSTEXPR14 bitset_ref operator=(ref_type const &br) const noexcept { ref = br; return *this; }
	template<std::size_t M>
	constexpr bitset_ref operator=(bitset_ref<M> br) const noexcept { return *this = static_cast<bool>(br); }
	constexpr bitset_ref operator=(bitset_ref<N> br) const noexcept { return *this = static_cast<ref_type>(br); }
	constexpr operator bool() const noexcept { return static_cast<bool>(ref); }
	constexpr operator ref_type() const noexcept { return ref; }
	constexpr bool operator~() const noexcept { return ~ref; }
	CONSTEXPR14 bitset_ref &flip() const noexcept { ref.flip(); return *this; }

	// I/O
	template<typename Ch, typename Tr>
	finline friend inline std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, bitset_ref br)
	{
		bool x;
		is >> x;
		br = x;
		return is;
	}
};

template<std::size_t N>
static constexpr bitset_ref<N> bit(typename std::bitset<N>::reference ref) noexcept
{
	return bitset_ref<N>(ref);
}
template<std::size_t N>
static constexpr bitset_ref<N> bit(std::bitset<N> &bs, std::size_t pos) noexcept
{
	return bitset_ref<N>(bs[pos]);
}


// Custom fixed- or dynamic-sized bitset/integer
// TODO
template<std::size_t N = dynamic_extent, bool S = true>
struct uint_big_t
{

};

// I/O
template<typename T, typename Ch = char, typename Tr = std::char_traits<Ch>>
finline static inline T sread(std::basic_istream<Ch, Tr> &is = std::cin)
{
	T x;
	is >> x;
	return x;
}

char constexpr nl = '\n';

// General I/O declarations
// In global namespace due to ADL
template<typename C>
struct enable_range_io : public std::true_type {};
template<typename Ch, typename Tr, typename A>
struct enable_range_io<std::basic_string<Ch, Tr, A>> : public std::false_type {};
#if CPP_17
template<typename Ch, typename Tr>
struct enable_range_io<std::basic_string_view<Ch, Tr>> : public std::false_type {};
#endif
template<typename Ch, typename Tr, typename C>
struct has_range_io;

template<std::size_t I = 0, typename Ch, typename Tr, typename Tup>
finline static inline typename std::enable_if<I >= std::tuple_size<typename std::remove_reference<Tup>::type>::value, void>::type
read_tuple(std::basic_istream<Ch, Tr> &, Tup &&);
template<std::size_t I = 0, typename Ch, typename Tr, typename Tup>
finline static inline typename std::enable_if < I < std::tuple_size<typename std::remove_reference<Tup>::type>::value, void>::type
	read_tuple(std::basic_istream<Ch, Tr> &is, Tup &&tup);

template<std::size_t I = 0, typename Ch, typename Tr, typename Tup>
finline static inline typename std::enable_if<I >= std::tuple_size<typename std::remove_reference<Tup>::type>::value, void>::type
write_tuple(std::basic_ostream<Ch, Tr> &, Tup &&);
template<std::size_t I = 0, typename Ch, typename Tr, typename Tup>
finline static inline typename std::enable_if < I < std::tuple_size<typename std::remove_reference<Tup>::type>::value, void>::type
	write_tuple(std::basic_ostream<Ch, Tr> &is, Tup &&tup);

template<typename Ch, typename Tr, typename C>
finline static inline typename std::enable_if<has_range_io<Ch, Tr, C>::read, std::basic_istream<Ch, Tr> &>::type
operator>>(std::basic_istream<Ch, Tr> &is, C &&c);
template<typename Ch, typename Tr, typename C>
finline static inline typename std::enable_if<has_range_io<Ch, Tr, C>::write, std::basic_ostream<Ch, Tr> &>::type
operator<<(std::basic_ostream<Ch, Tr> &os, C &&c);

template<typename Ch, typename Tr, typename Tup, std::size_t = std::tuple_size<typename std::remove_reference<Tup>::type>::value>
finline static inline std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, Tup &&tup);
template<typename Ch, typename Tr, typename Tup, std::size_t = std::tuple_size<typename std::remove_reference<Tup>::type>::value>
finline static inline std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, Tup &&tup);

// - General I/O implementations
#define IO_IMPL \
template<typename Ch, typename Tr, typename C> \
struct has_range_io \
{ \
	typedef std::basic_istream<Ch, Tr> Is; \
	typedef std::basic_ostream<Ch, Tr> Os; \
	template<typename T> \
	static auto check_read(int) -> decltype( \
		std::declval<Is &>() >> *std::begin(std::declval<T &>()), \
		std::end(std::declval<T &>()), \
		std::true_type{} \
	); \
	template<typename T> \
	static auto check_write(int) -> decltype( \
		std::declval<Os &>() << *std::begin(std::declval<T const &>()), \
		std::end(std::declval<T &>()), \
		std::true_type{} \
	); \
	template<typename> static std::false_type check_read(...); \
	template<typename> static std::false_type check_write(...); \
	typedef typename std::decay<C>::type D; \
	static constexpr bool enabled = \
		!std::is_same<Ch, typename std::remove_cv<typename std::remove_pointer<D>::type>::type>::value && \
		enable_range_io<D>::value; \
	static constexpr bool read = enabled && decltype(check_read<C>(0))::value; \
	static constexpr bool write = enabled && decltype(check_write<C>(0))::value; \
}; \
template<std::size_t I, typename Ch, typename Tr, typename Tup> \
finline static inline typename std::enable_if<I >= std::tuple_size<typename std::remove_reference<Tup>::type>::value, void>::type \
read_tuple(std::basic_istream<Ch, Tr> &, Tup &&) {} \
template<std::size_t I, typename Ch, typename Tr, typename Tup> \
finline static inline typename std::enable_if < I < std::tuple_size<typename std::remove_reference<Tup>::type>::value, void>::type \
	read_tuple(std::basic_istream<Ch, Tr> &is, Tup &&tup) \
{ \
	is >> std::get<I>(static_cast<Tup &&>(tup)); \
	read_tuple<I + 1>(is, static_cast<Tup &&>(tup)); \
} \
template<std::size_t I, typename Ch, typename Tr, typename Tup> \
finline static inline typename std::enable_if<I >= std::tuple_size<typename std::remove_reference<Tup>::type>::value, void>::type \
write_tuple(std::basic_ostream<Ch, Tr> &, Tup &&) {} \
template<std::size_t I, typename Ch, typename Tr, typename Tup> \
finline static inline typename std::enable_if < I < std::tuple_size<typename std::remove_reference<Tup>::type>::value, void>::type \
	write_tuple(std::basic_ostream<Ch, Tr> &os, Tup &&tup) \
{ \
	static constexpr auto delim = ' '; \
	if (I) \
		os << delim; \
	os << std::get<I>(static_cast<Tup &&>(tup)); \
	write_tuple<I + 1>(os, static_cast<Tup &&>(tup)); \
} \
template<typename Ch, typename Tr, typename Tup, std::size_t> \
finline static inline std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, Tup &&tup) \
{ \
	read_tuple(is, static_cast<Tup &&>(tup)); \
	return is; \
} \
template<typename Ch, typename Tr, typename Tup, std::size_t> \
finline static inline std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, Tup &&tup) \
{ \
	write_tuple(os, static_cast<Tup &&>(tup)); \
	return os; \
} \
template<typename Ch, typename Tr, typename C> \
finline static inline typename std::enable_if<has_range_io<Ch, Tr, C>::read, std::basic_istream<Ch, Tr> &>::type \
operator>>(std::basic_istream<Ch, Tr> &is, C &&c) \
{ \
	auto const last = std::end(c); \
	for (auto it = std::begin(c); it != last; ++it) \
		is >> *it; \
	return is; \
} \
template<typename Ch, typename Tr, typename C> \
finline static inline typename std::enable_if<has_range_io<Ch, Tr, C>::write, std::basic_ostream<Ch, Tr> &>::type \
operator<<(std::basic_ostream<Ch, Tr> &os, C &&c) \
{ \
	static constexpr auto delim = ' '; \
	auto it = std::begin(c); \
	auto const last = std::end(c); \
	if (it != last) \
		os << *it; \
	while (++it != last) \
		os << delim << *it; \
	return os; \
}

// break_if and break_eq
// After one read or assignment, throws Exc{} if pred(ref).
// Meant to be used as a temporary in an istream >>  ...expression or an assignment.
template<typename T, typename P, typename E>
struct throw_if_impl;

template<typename E, typename T, typename P>
finline NODISCARD static constexpr throw_if_impl<T, P, E> throw_if(T &&reference, P &&predicate) noexcept;

template<typename T, typename P, typename E>
struct throw_if_impl
{
	typedef T read_type;
	typedef P predicate_type;
	typedef E exception_type;

	read_type val;
	predicate_type pred;

	finline CNODISCARD constexpr throw_if_impl(read_type &&reference, predicate_type &&predicate) noexcept :
		val(static_cast<read_type &&>(reference)),
		pred(static_cast<predicate_type &&>(predicate))
	{}

	finline CONSTEXPR14 void check() const
	{
		if (pred(val))
			throw exception_type{};
	}

	template<typename U>
	finline CONSTEXPR14 read_type &operator=(U &&value) const
	{
		val = static_cast<U &&>(value);
		check();
		return val;
	}

	template<typename Ch, typename Tr>
	finline friend inline std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, throw_if_impl const &ti)
	{
		is >> ti.val;
		ti.check();
		return is;
	}
};
template<typename E, typename T, typename P>
finline NODISCARD static constexpr throw_if_impl<T, P, E> throw_if(T &&reference, P &&predicate) noexcept
{
	return throw_if_impl<T, P, E>(static_cast<T &&>(reference), static_cast<P &&>(predicate));
}

template<typename T>
struct eq_pred
{
	T val;
	finline CNODISCARD constexpr eq_pred(T value) noexcept :
		val(static_cast<T &&>(value))
	{}
	template<typename U>
	finline NODISCARD constexpr bool operator()(U &&value) const noexcept
	{
		return val == static_cast<U &&>(value);
	}
};

template<typename T, typename P>
finline NODISCARD static constexpr throw_if_impl<T, P, tc_break> break_if(T &&reference, P &&predicate) noexcept
{
	return throw_if<tc_break>(static_cast<T &&>(reference), static_cast<P &&>(predicate));
}

template<typename U, typename T>
finline NODISCARD static constexpr throw_if_impl<T, eq_pred<U>, tc_break> break_eq(T &&reference, U &&value) noexcept
{
	return break_if(static_cast<T &&>(reference), eq_pred<U>(static_cast<U &&>(value)));
}

// sizer
template<typename ...Cs>
struct size_ref
{
	finline CNODISCARD constexpr size_ref() noexcept {}
	finline CNODISCARD constexpr size_ref(size_ref const &) noexcept = default;
	finline CNODISCARD constexpr size_ref(size_ref &&) noexcept = default;
	size_ref &operator=(const size_ref &) = delete;
	size_ref &operator=(size_ref &&) noexcept = delete;
	finline CONSTEXPR14 size_ref &operator=(std::size_t) noexcept
	{
		return *this;
	}
	finline CONSTEXPR14 size_ref const &operator=(std::size_t) const noexcept
	{
		return *this;
	}
};
template<typename C, typename ...Cs>
struct size_ref<C, Cs...> : public size_ref<Cs...>
{
	C &c;
	template<typename ...Args>
	finline CNODISCARD constexpr size_ref(C &container, Args &&... args) noexcept :
		size_ref<Cs...>(static_cast<Args &&>(args)...),
		c(container)
	{}
	finline CNODISCARD constexpr size_ref(size_ref const &) noexcept = default;
	finline CNODISCARD constexpr size_ref(size_ref &&) noexcept = default;
	size_ref &operator=(const size_ref &) = delete;
	size_ref &operator=(size_ref &&) noexcept = delete;
	finline NODISCARD constexpr operator std::size_t() const noexcept
	{
		return size(c);
	}
	finline CONSTEXPR14 size_ref &operator=(std::size_t size) noexcept
	{
		c.resize(size);
		size_ref<Cs...>::operator=(size);
		return *this;
	}
	finline CONSTEXPR14 size_ref const &operator=(std::size_t size) const noexcept
	{
		c.resize(size);
		size_ref<Cs...>::operator=(size);
		return *this;
	}
};
template<typename C, typename ...TArgs, typename ...Cs>
struct size_ref<std::tuple<C &, TArgs...>, Cs...> : public size_ref<Cs...>
{
	C &c;
	typename C::value_type val;
private:
	template<typename Tup, std::size_t ...Is, typename ...Args>
	finline CNODISCARD constexpr size_ref(Tup &&tup, index_sequence<Is...>, Args &&... args) noexcept :
		size_ref<Cs...>(static_cast<Args &&>(args)...),
		c(std::get<0>(tup)),
		val(std::get<Is + 1>(tup)...)
	{}
public:
	template<typename Tup, typename ...Args>
	finline CNODISCARD constexpr size_ref(Tup &&tup, Args &&... args) noexcept :
		size_ref(
			tup,
			make_index_sequence<std::tuple_size<typename std::remove_cv<typename std::remove_reference<Tup>::type>::type>::value - 1>{},
			static_cast<Args &&>(args)...
		)
	{}
	finline CNODISCARD constexpr size_ref(size_ref const &) noexcept = default;
	finline CNODISCARD constexpr size_ref(size_ref &&) noexcept = default;
	size_ref &operator=(const size_ref &) = delete;
	size_ref &operator=(size_ref &&) noexcept = delete;
	finline NODISCARD constexpr operator std::size_t() const noexcept
	{
		return size(c);
	}
	finline CONSTEXPR14 size_ref &operator=(std::size_t size) noexcept
	{
		c.resize(size, val);
		size_ref<Cs...>::operator=(size);
		return *this;
	}
	finline CONSTEXPR14 size_ref const &operator=(std::size_t size) const noexcept
	{
		c.resize(size, val);
		size_ref<Cs...>::operator=(size);
		return *this;
	}
};
template<typename ...Cs>
finline static inline size_ref<typename std::remove_const<typename std::remove_reference<Cs>::type>::type...> sizer(Cs &&... containers) noexcept
{
	return size_ref<typename std::remove_cv<typename std::remove_reference<Cs>::type>::type...>(static_cast<Cs &&>(containers)...);
}
template<typename Ch, typename Tr, typename ...Cs>
finline static inline std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, size_ref<Cs...> const &sr)
{
	sr = sread<std::size_t>(is);
	return is;
}

// ACT, TACT
template<typename F, typename R = decltype(std::declval<F>()())>
struct io_action
{
	// TODO static_assert for nice error messages
	typedef F function_type;
	typedef R return_type;
	F f;
	finline CNODISCARD constexpr io_action(F &&fn) :
		f(static_cast<F &&>(fn))
	{}
	template<typename Ch, typename Tr>
	finline void read(std::basic_istream<Ch, Tr> &is) const
	{
		is >> f();
	}
	template<typename Ch, typename Tr>
	finline void write(std::basic_ostream<Ch, Tr> &os) const
	{
		os << f();
	}
};
template<typename F>
struct io_action<F, void>
{
	// TODO static_assert for nice error messages
	typedef F function_type;
	typedef void return_type;
	F f;
	finline CNODISCARD constexpr io_action(F &&fn) :
		f(static_cast<F &&>(fn))
	{}
	template<typename Ch, typename Tr>
	finline void read(std::basic_istream<Ch, Tr> &) const
	{
		f();
	}
	template<typename Ch, typename Tr>
	finline void write(std::basic_ostream<Ch, Tr> &) const
	{
		f();
	}
};
template<typename Ch, typename Tr, typename F>
finline static inline std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, io_action<F> const &act)
{
	act.read(is);
	return is;
}
template<typename Ch, typename Tr, typename F>
finline static inline std::basic_ostream<Ch, Tr> &operator<<(std::basic_ostream<Ch, Tr> &os, io_action<F> const &act)
{
	act.write(os);
	return os;
}
template<typename F>
finline static inline io_action<F> act(F &&fn) noexcept
{
	return io_action<F>(static_cast<F &&>(fn));
}
#define ACT(body1, ...) act([&]() { body1, ## __VA_ARGS__ })
#define TACT(type, body1, ...) act([&]() -> type { body1, ## __VA_ARGS__ })


// tie with rvalue reference support; equivalent to std::forward_as_tuple
template<typename ...Ts>
finline static constexpr std::tuple<Ts &&...> rtie(Ts &&... args) noexcept
{
	return std::tuple<Ts &&...>(static_cast<Ts &&>(args)...);
}

// settings forward declarations
extern bool const TEST_CASES;
extern bool const DEBUG_FILE;
extern bool const TC_NUMBERS;

finline static inline void pre();
finline static inline void go(std::size_t tc);
finline static inline void post();

#ifdef DEBUG
int main(int argc, char const *argv[])
#else
int main()
#endif
{
	std::cin.tie(nullptr);
	std::ios::sync_with_stdio(false);
#ifdef DEBUG
	if (DEBUG_FILE && argc > 2)
	{
		std::ignore = std::freopen(argv[1], "r", stdin);
		std::ignore = std::freopen(argv[2], "w", stdout);
	}
#endif

	pre();

	std::size_t TC = TEST_CASES ? sread<std::size_t>() : 0;
	for (std::size_t tc = 0; !TEST_CASES || tc < TC; tc++)
	{
		if (TC_NUMBERS)
			std::cout << "Case " << tc + 1 << ": ";
		try
		{
			go(tc);
		}
		catch (tc_continue)
		{
			continue;
		}
		catch (tc_break)
		{
			break;
		}
		if (!TEST_CASES)
			break;
	}

	post();
	return 0;
}

using namespace std;
using namespace chrono;

// typedefs
#define TDEFS1(T)using p##T=pair<T,T>;using a2##T=array<T,2>;using v##T=vector<T>;using v##p##T=vector<p##T>;using v##a2##T=vector<a2##T>;using vv##T=vector<v##T>;using vv##p##T=vector<v##p##T>;using vv##a2##T=vector<v##a2##T>;using vvv##T=vector<vv##T>;using vvv##p##T=vector<vv##p##T>;using vvv##a2##T=vector<vv##a2##T>;using vvvv##T=vector<vvv##T>;using vvvv##p##T=vector<vvv##p##T>;using vvvv##a2##T=vector<vvv##a2##T>;using l##T=list<T>;using l##p##T=list<p##T>;using l##a2##T=list<a2##T>;using vl##T=vector<l##T>;using vl##p##T=vector<l##p##T>;using vl##a2##T=vector<l##a2##T>;using s##T=set<T>;using s##p##T=set<p##T>;using s##a2##T=set<a2##T>;using vs##T=vector<s##T>;using vs##p##T=vector<s##p##T>;using vs##a2##T=vector<s##a2##T>;template<class Pr> using S##T=set<T,Pr>;template<class Pr> using S##p##T=set<p##T,Pr>;template<class Pr> using S##a2##T=set<a2##T,Pr>;template<class Pr> using vS##T=vector<S##T<Pr>>;template<class Pr> using vS##p##T=vector<S##p##T<Pr>>;template<class Pr> using vS##a2##T=vector<S##a2##T<Pr>>;using ms##T=multiset<T>;using ms##p##T=multiset<p##T>;using ms##a2##T=multiset<a2##T>;using vms##T=vector<ms##T>;using vms##p##T=vector<ms##p##T>;using vms##a2##T=vector<ms##a2##T>;template<class Pr> using MS##T=multiset<T,Pr>;template<class Pr> using MS##p##T=multiset<p##T,Pr>;template<class Pr> using MS##a2##T=multiset<a2##T,Pr>;template<class Pr> using vMS##T=vector<MS##T<Pr>>;template<class Pr> using vMS##p##T=vector<MS##p##T<Pr>>;template<class Pr> using vMS##a2##T=vector<MS##a2##T<Pr>>;using us##T=unordered_set<T>;using us##p##T=unordered_set<p##T>;using us##a2##T=unordered_set<a2##T>;using vus##T=vector<us##T>;using vus##p##T=vector<us##p##T>;using vus##a2##T=vector<us##a2##T>;template<class H,class Eq> using US##T=unordered_set<T,H,Eq>;template<class H,class Eq> using US##p##T=unordered_set<p##T,H,Eq>;template<class H,class Eq> using US##a2##T=unordered_set<a2##T,H,Eq>;template<class H,class Eq> using vUS##T=vector<US##T<H,Eq>>;template<class H,class Eq> using vUS##p##T=vector<US##p##T<H,Eq>>;template<class H,class Eq> using vUS##a2##T=vector<US##a2##T<H,Eq>>;using ums##T=unordered_multiset<T>;using ums##p##T=unordered_multiset<p##T>;using ums##a2##T=unordered_multiset<a2##T>;using vums##T=vector<ums##T>;using vums##p##T=vector<ums##p##T>;using vums##a2##T=vector<ums##a2##T>;template<class H,class Eq> using UMS##T=unordered_multiset<T,H,Eq>;template<class H,class Eq> using UMS##p##T=unordered_multiset<p##T,H,Eq>;template<class H,class Eq> using UMS##a2##T=unordered_multiset<a2##T,H,Eq>;template<class H,class Eq> using vUMS##T=vector<UMS##T<H,Eq>>;template<class H,class Eq> using vUMS##p##T=vector<UMS##p##T<H,Eq>>;template<class H,class Eq> using vUMS##a2##T=vector<UMS##a2##T<H,Eq>>;using q##T=queue<T>;using q##p##T=queue<p##T>;using q##a2##T=queue<a2##T>;using vq##T=vector<q##T>;using vq##p##T=vector<q##p##T>;using vq##a2##T=vector<q##a2##T>;using d##T=deque<T>;using d##p##T=deque<p##T>;using d##a2##T=deque<a2##T>;using vd##T=vector<d##T>;using vd##p##T=vector<d##p##T>;using vd##a2##T=vector<d##a2##T>;using pq##T=priority_queue<T>;using pq##p##T=priority_queue<p##T>;using pq##a2##T=priority_queue<a2##T>;using vpq##T=vector<pq##T>;using vpq##p##T=vector<pq##p##T>;using vpq##a2##T=vector<pq##a2##T>;template<class Pr> using PQ##T=priority_queue<T,v##T,Pr>;template<class Pr> using PQ##p##T=priority_queue<p##T,v##p##T,Pr>;template<class Pr> using PQ##a2##T=priority_queue<a2##T,v##a2##T,Pr>;template<class Pr> using vPQ##T=vector<PQ##T<Pr>>;template<class Pr> using vPQ##p##T=vector<PQ##p##T<Pr>>;template<class Pr> using vPQ##a2##T=vector<PQ##a2##T<Pr>>;
#define TDEFS2(T,N)using N=T;TDEFS1(N)
TDEFS2(bool, bl);
TDEFS2(char, c8);
TDEFS2(unsigned char, uc8);
TDEFS2(int8_t, i8);
TDEFS2(uint8_t, u8);
TDEFS2(int16_t, i16);
TDEFS2(uint16_t, u16);
TDEFS2(int32_t, i32);
TDEFS2(uint32_t, u32);
TDEFS2(int64_t, i64)
TDEFS2(uint64_t, u64);
TDEFS2(float, f32);
TDEFS2(double, f64);
TDEFS2(long double, f80);
#if COMPILER == GCC || COMPILER == CLANG
TDEFS2(__int128_t, i128);
TDEFS2(__uint128_t, u128);
TDEFS2(__float128, f128);
#endif
TDEFS2(string, st8);

template<typename T>
constexpr T MIN = numeric_limits<T>::min();
template<class T>
constexpr T MAX = numeric_limits<T>::max();
template<class T>
constexpr T INF = numeric_limits<T>::infinity();

#define ALL(c) begin(c), end(c)
#define CALL(c) cbegin(c), cend(c)
#define RALL(c) rbegin(c), rend(c)
#define CRALL(c) crbegin(c), crend(c)

// Compatibility with ICPC team notebook code
#define rep(i, a, b) for (decltype((a) + (b)) i = (a); i < (b); ++i)
#define rrep(i, a, b) for (decltype((a) + (b)) i = (b) - 1; i >= (a); --i)
#define srep(i, a, b, s) for (decltype((a) + (b) + s) i = (a); i < (b); i += (s))
#define srrep(i, a, b, s) for (decltype((a) + (b) + s) i = (b) - 1; i >= (a); i -= (s))
#define all(c) begin(c), end(c)
#define rall(c) rbegin(c), rend(c)
typedef long long ll;
typedef pi32 pii;
typedef a2i32 aii;
typedef vi32 vi;
typedef vvi32 vvi;
typedef vi64 vll;
typedef vbl vb;
mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());

// g++ -fdiagnostics-color=always -std=c++20 -Wall -Wextra -Wconversion -Wshadow -Werror -static -Wl,--stack=268435456 -fno-ms-extensions -DDEBUG -g ./template.cpp -o ./main
// clang++ -stdlib=libc++ -fdiagnostics-color=always -std=c++20 -Wall -Wextra -Wconversion -Wshadow -Werror -static -Wl,--stack=268435456 -fno-ms-extensions -DDEBUG -g ./template.cpp -o ./main

bool const TEST_CASES = 1;
bool const DEBUG_FILE = 1;
bool const TC_NUMBERS = 1;

IO_IMPL

int m;
vpi32 A, B, C;
vbl D;
vi32 L, R;

auto const C1 = [](int a, int b) { return B[a] < B[b]; };
auto const C2 = [](int a, int b) { return C[a] < C[b]; };

bool works(int t)
{
	fill(ALL(D), false);
	int a = 0, b = (int)A.size() - 1;

	// given m = min t+x, put a point at fixed t and t+x (x = m - t)
	int ct = 0;
	while (b >= 0)
	{
		while (D[L[a]])
			a++;
		ct++;
		int i = L[a];
		int x = B[i].first - t;
		while (b >= 0)
		{
			int j = R[b];
			if (C[j].first >= t - x)
			{
				b--;
				D[j] = true;
			}
			else
				break;
		}
	}

	return ct <= m;
}

static inline void pre()
{

}

static inline void post()
{

}

static inline void go(size_t)
{
	cin >> sizer(A, B, C, D, L, R) >> m >> A;
	rep(i, 0, size(A))
	{
		B[i] = { A[i].first + A[i].second, i };
		C[i] = { A[i].first - A[i].second, i };
		L[i] = R[i] = (int)i;
	}

	sort(ALL(L), C1);
	sort(ALL(R), C2);

	int lo = -2000000, hi = min_element(ALL(A))->first;

	while (lo < hi)
	{
		int mid = (lo + hi + 2000001) / 2 - 1000000;
		if (works(mid))
			lo = mid;
		else
			hi = mid - 1;
	}

	cout << lo << '\n';
}

#if COMPILER == CLANG
#pragma clang attribute pop
#endif
