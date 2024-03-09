// Author: Evan Bailey

// preprocessor flags
#define GCC 0
#define CLANG 1
#define MSVC 2

#if defined(__clang__)
#define COMPILER CLANG
#elif defined(__GNUC__)
#define COMPILER GCC
#elif defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#define COMPILER MSVC
#endif

#ifndef COMPILER
#error "Unknown Compiler"
#endif

#define VER_98 
#define VER_11 
#define VER_14 
#define VER_17 
#define VER_20 
#define VER_23 

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

#if !CPP_14
#error "C++ standard before C++17"
#endif // TODO allow C++14

// optimization pragmas
#if !DEBUG && COMPILER == C_GCC
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
#include <memory_resource>
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

// STL header replacement
#if !CPP_20
// TODO bit
namespace numbers
{
// TODO numbers

};
// TODO span
#endif

// util
#if !CPP_17
namespace std
{
template<typename C>
std::size_t size(C const &c) { return c.size(); }
template<typename T, std::size_t N>
std::size_t size(T const [N]) { return N; }
}
#endif

// I/O
template<typename T, typename Is = std::istream>
T read(Is &is = std::cin)
{
	T ans;
	is >> ans;
	return ans;
}

// basic container I/O

// - declarations
namespace impl
{
template<typename Ch, typename Tr, typename C>
struct is_range_readable
{
	typedef std::basic_istream<Ch, Tr> Is;
	template<typename T>
	static auto check(int) -> decltype(
		std::declval<Is &>() >> *std::begin(std::declval<T &>()),
		std::end(std::declval<T &>()),
		std::true_type{}
	);
	template<typename>
	static std::false_type check(...);
	static constexpr bool value = decltype(check<C>(0))::value;
};

template<std::size_t I = 0, typename Ch, typename Tr, typename... Ts>
std::enable_if_t<I == sizeof...(Ts), void>
read_tuple(std::basic_istream<Ch, Tr> &, std::tuple<Ts...> &);

template<std::size_t I = 0, typename Ch, typename Tr, typename... Ts>
std::enable_if_t < I < sizeof...(Ts), void>
	read_tuple(std::basic_istream<Ch, Tr> &is, std::tuple<Ts...> &t);
}

template<typename Ch, typename Tr, typename C>
std::enable_if_t<impl::is_range_readable<Ch, Tr, C>::value, std::basic_istream<Ch, Tr> &>
operator>>(std::basic_istream<Ch, Tr> &is, C &c);

template<typename T, typename U, typename Ch, typename Tr>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::pair<T, U> &p);

template<typename Ch, typename Tr, typename... Ts>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::tuple<Ts...> &t);

template<typename Ch, typename Tr, typename... Ts>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::tuple<Ts&...> t);

// - implementations
template<std::size_t I, typename Ch, typename Tr, typename... Ts>
std::enable_if_t<I == sizeof...(Ts), void>
impl::read_tuple(std::basic_istream<Ch, Tr> &, std::tuple<Ts...> &)
{}

template<std::size_t I, typename Ch, typename Tr, typename... Ts>
std::enable_if_t < I < sizeof...(Ts), void>
	impl::read_tuple(std::basic_istream<Ch, Tr> &is, std::tuple<Ts...> &t)
{
	is >> std::get<I>(t);
	read_tuple<I + 1>(is, t);
}

template<typename Ch, typename Tr, typename C>
std::enable_if_t<impl::is_range_readable<Ch, Tr, C>::value, std::basic_istream<Ch, Tr> &>
operator>>(std::basic_istream<Ch, Tr> &is, C &c)
{
	for (auto &x : c)
		is >> x;
	return is;
}

template<typename T, typename U, typename Ch, typename Tr>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::pair<T, U> &p)
{
	return is >> p.first >> p.second;
}

template<typename Ch, typename Tr, typename... Ts>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::tuple<Ts...> &t)
{
	impl::read_tuple(is, t);
	return is;
}

template<typename Ch, typename Tr, typename... Ts>
std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, std::tuple<Ts&...> t)
{
	impl::read_tuple(is, t);
	return is;
}

// sizer
template<typename C>
struct sizer
{
	typedef C container_type;
	typedef typename C::size_type size_type;
	typedef typename C::value_type value_type;

	C &c;
	value_type x;

	[[nodiscard]] constexpr sizer(C &container, value_type &&fill = value_type{}) noexcept :
		c(container),
		x(std::forward<value_type>(fill))
	{}
	[[nodiscard]] constexpr operator size_type() const noexcept
	{
		using std::size;
		return size(c);
	}
	[[nodiscard]] constexpr operator int() const noexcept
	{
		using std::size;
		return (int)size(c);
	}
	constexpr sizer &operator=(size_type size) noexcept
	{
		c.resize(size, x);
	}
	template<typename Ch, typename Tr>
	friend std::basic_istream<Ch, Tr> &operator>>(std::basic_istream<Ch, Tr> &is, sizer &sr)
	{
		sr = read<sizer<C>::size_type>(is);
		return is;
	}
};

// testcase control flow exceptions
struct tc_break {};
struct tc_continue {};

// settings declarations
extern bool const TST_CASES;
extern bool const DBG_FILES;
extern bool const PRINT_TCS;

void pre();
void go(std::size_t tc);
void post();

int main(int argc, char const *argv[])
{
	std::cin.tie(nullptr);
	std::ios::sync_with_stdio(false);
	if (DBG_FILES && argc > 2)
	{
		std::ignore = std::freopen(argv[1], "r", stdin);
		std::ignore = std::freopen(argv[2], "w", stdout);
	}

	pre();

	std::size_t TC = TST_CASES ? read<std::size_t>() : 0;
	for (std::size_t tc = 0; !TST_CASES || tc < TC; tc++)
	{
		try
		{
			if (PRINT_TCS)
			{
				std::cout << "Case #" << tc + 1 << ": ";
			}
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
	}

	post();
	return 0;
}

using namespace std;

#define TDEFS1(T)using p##T=pair<T,T>;using a2##T=array<T,2>;using v##T=vector<T>;using v##p##T=vector<p##T>;using v##a2##T=vector<a2##T>;using vv##T=vector<v##T>;using vv##p##T=vector<v##p##T>;using vv##a2##T=vector<v##a2##T>;using vvv##T=vector<vv##T>;using vvv##p##T=vector<vv##p##T>;using vvv##a2##T=vector<vv##a2##T>;using vvvv##T=vector<vvv##T>;using vvvv##p##T=vector<vvv##p##T>;using vvvv##a2##T=vector<vvv##a2##T>;using l##T=list<T>;using l##p##T=list<p##T>;using l##a2##T=list<a2##T>;using vl##T=vector<l##T>;using vl##p##T=vector<l##p##T>;using vl##a2##T=vector<l##a2##T>;using s##T=set<T>;using s##p##T=set<p##T>;using s##a2##T=set<a2##T>;using vs##T=vector<s##T>;using vs##p##T=vector<s##p##T>;using vs##a2##T=vector<s##a2##T>;template<class Pr> using S##T=set<T,Pr>;template<class Pr> using S##p##T=set<p##T,Pr>;template<class Pr> using S##a2##T=set<a2##T,Pr>;template<class Pr> using vS##T=vector<S##T<Pr>>;template<class Pr> using vS##p##T=vector<S##p##T<Pr>>;template<class Pr> using vS##a2##T=vector<S##a2##T<Pr>>;using ms##T=multiset<T>;using ms##p##T=multiset<p##T>;using ms##a2##T=multiset<a2##T>;using vms##T=vector<ms##T>;using vms##p##T=vector<ms##p##T>;using vms##a2##T=vector<ms##a2##T>;template<class Pr> using MS##T=multiset<T,Pr>;template<class Pr> using MS##p##T=multiset<p##T,Pr>;template<class Pr> using MS##a2##T=multiset<a2##T,Pr>;template<class Pr> using vMS##T=vector<MS##T<Pr>>;template<class Pr> using vMS##p##T=vector<MS##p##T<Pr>>;template<class Pr> using vMS##a2##T=vector<MS##a2##T<Pr>>;using us##T=unordered_set<T>;using us##p##T=unordered_set<p##T>;using us##a2##T=unordered_set<a2##T>;using vus##T=vector<us##T>;using vus##p##T=vector<us##p##T>;using vus##a2##T=vector<us##a2##T>;template<class H,class Eq> using US##T=unordered_set<T,H,Eq>;template<class H,class Eq> using US##p##T=unordered_set<p##T,H,Eq>;template<class H,class Eq> using US##a2##T=unordered_set<a2##T,H,Eq>;template<class H,class Eq> using vUS##T=vector<US##T<H,Eq>>;template<class H,class Eq> using vUS##p##T=vector<US##p##T<H,Eq>>;template<class H,class Eq> using vUS##a2##T=vector<US##a2##T<H,Eq>>;using ums##T=unordered_multiset<T>;using ums##p##T=unordered_multiset<p##T>;using ums##a2##T=unordered_multiset<a2##T>;using vums##T=vector<ums##T>;using vums##p##T=vector<ums##p##T>;using vums##a2##T=vector<ums##a2##T>;template<class H,class Eq> using UMS##T=unordered_multiset<T,H,Eq>;template<class H,class Eq> using UMS##p##T=unordered_multiset<p##T,H,Eq>;template<class H,class Eq> using UMS##a2##T=unordered_multiset<a2##T,H,Eq>;template<class H,class Eq> using vUMS##T=vector<UMS##T<H,Eq>>;template<class H,class Eq> using vUMS##p##T=vector<UMS##p##T<H,Eq>>;template<class H,class Eq> using vUMS##a2##T=vector<UMS##a2##T<H,Eq>>;using q##T=queue<T>;using q##p##T=queue<p##T>;using q##a2##T=queue<a2##T>;using vq##T=vector<q##T>;using vq##p##T=vector<q##p##T>;using vq##a2##T=vector<q##a2##T>;using d##T=deque<T>;using d##p##T=deque<p##T>;using d##a2##T=deque<a2##T>;using vd##T=vector<d##T>;using vd##p##T=vector<d##p##T>;using vd##a2##T=vector<d##a2##T>;using pq##T=priority_queue<T>;using pq##p##T=priority_queue<p##T>;using pq##a2##T=priority_queue<a2##T>;using vpq##T=vector<pq##T>;using vpq##p##T=vector<pq##p##T>;using vpq##a2##T=vector<pq##a2##T>;template<class Pr> using PQ##T=priority_queue<T,v##T,Pr>;template<class Pr> using PQ##p##T=priority_queue<p##T,v##p##T,Pr>;template<class Pr> using PQ##a2##T=priority_queue<a2##T,v##a2##T,Pr>;template<class Pr> using vPQ##T=vector<PQ##T<Pr>>;template<class Pr> using vPQ##p##T=vector<PQ##p##T<Pr>>;template<class Pr> using vPQ##a2##T=vector<PQ##a2##T<Pr>>;
#define TDEFS2(T,N)using N=T;TDEFS1(N)
TDEFS2(bool, bl);
TDEFS2(char, c8);
TDEFS2(unsigned char, uc8);
TDEFS2(int8_t, i8);
TDEFS2(int16_t, i16);
TDEFS2(int32_t, i32);
TDEFS2(int64_t, i64)
TDEFS2(__int128, i128);
TDEFS2(uint8_t, u8);
TDEFS2(uint16_t, u16);
TDEFS2(uint32_t, u32);
TDEFS2(uint64_t, u64);
TDEFS2(unsigned __int128, u128);
TDEFS2(float, f32);
TDEFS2(double, f64);
TDEFS2(long double, fld);
TDEFS2(__float128, f128);
TDEFS2(string, str8);

// g++ -std=gnu++20 -Wall -Wextra -Wconversion -Wshadow -Werror=return-type -static -fconcepts-diagnostics-depth=1 -fdiagnostics-color=always -fno-ms-extensions -DDEBUG -g template.cpp -o $./main

bool const TST_CASES = 1;
bool const DBG_FILES = 1;
bool const PRINT_TCS = 0;

void pre()
{

}

void post()
{

}

void go([[maybe_unused]] size_t tc)
{
	int n, m;

	throw tc_break{};
}

