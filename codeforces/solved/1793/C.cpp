#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#ifdef DEBUG
#define DBG(x) x
#define dassert(x) assert(x)
#else
#define DBG(x)
#define dassert(x) do {} while (0)
#endif

using namespace std;
using namespace chrono;
using namespace string_literals;
using namespace __gnu_pbds;

template<size_t S, class... Ts>
struct TupleHashHelper
{
	typedef std::tuple<Ts...> Tup;
	typedef TupleHashHelper<S - 1, Ts...> Helper;
	typedef std::tuple_element_t<S - 1, Tup> T;
	inline constexpr size_t operator()(const Tup& t) const noexcept
	{
		return (size_t)31 * Helper()(t) + std::hash<T>()(std::get<S - 1>(t));
	}
};

template<class... Ts>
struct TupleHashHelper<0, Ts...>
{
	typedef std::tuple<Ts...> Tup;
	inline constexpr size_t operator()(const Tup&) const noexcept
	{
		return 0;
	}
};

template<class... Ts>
struct std::hash<tuple<Ts...>>
{
	typedef std::tuple<Ts...> Tup;
	static constexpr size_t S = sizeof...(Ts);
	typedef TupleHashHelper<S, Ts...> Helper;
	inline constexpr size_t operator()(const Tup& t) const noexcept
	{
		return Helper()(t);
	}
};

template<class T, class U>
struct std::hash<pair<T, U>>
{
	inline constexpr size_t operator()(const pair<T, U>& p) const noexcept
	{
		return (size_t)31 * hash<T>()(p.first) + hash<U>()(p.second);
	}
};

template<integral T> [[nodiscard]] constexpr T rup2(T x) noexcept
{
	if (x-- == 0) return 1;
	for (int i = 1; i < int(CHAR_BIT * sizeof(T)); i *= 2) x |= x >> i;
	return ++x;
}

/* iterator example
template<class T> class optional_iterator
{
private:
	T* val = nullptr;
	bool done = true;
	template<template<class> class C> constexpr bool cmp(const optional_iterator& it) const noexcept
	{
		dassert(val == it.val);
		return C<bool>()(done, it.done);
	}
public:
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = T*;
	using reference = T&;
	using iterator_category = random_access_iterator_tag;
	using iterator_concept = contiguous_iterator_tag;
	constexpr optional_iterator() noexcept = default;
	constexpr optional_iterator(optional<T>& opt) noexcept: val(opt ? &*opt : nullptr), done(opt) {}
	constexpr optional_iterator(const optional<T>& opt) noexcept: val(opt ? &*opt : nullptr), done(opt) {}
	constexpr optional_iterator& operator++() noexcept { dassert(!done); done = true; return *this; }
	constexpr optional_iterator& operator--() noexcept { dassert(done && opt && *opt); done = false; return *this; }
	constexpr [[nodiscard]] optional_iterator operator++(int) noexcept { auto it = *this; ++* this; return it; }
	constexpr [[nodiscard]] optional_iterator operator--(int) noexcept { auto it = *this; --* this; return it; }
	constexpr optional_iterator& operator+=(difference_type n) noexcept { dassert(done + n == 0 || done + n == 1); done = done + n; return *this; }
	constexpr optional_iterator& operator-=(difference_type n) noexcept { dassert(done - n == 0 || done - n == 1); done = done - n; return *this; }
	constexpr [[nodiscard]] optional_iterator operator+(difference_type n) const noexcept { optional_iterator it = *this; return it += n; }
	constexpr [[nodiscard]] optional_iterator operator-(difference_type n) const noexcept { optional_iterator it = *this; return it -= n; }
	constexpr [[nodiscard]] optional_iterator operator-(difference_type n) const noexcept { optional_iterator it = *this; return it -= n; }
	constexpr friend [[nodiscard]] optional_iterator operator+(difference_type n, const optional_iterator& it) noexcept { return it + n; }
	constexpr [[nodiscard]] optional_iterator operator-(const optional_iterator& it) { dassert(val == it.val); return static_cast<difference_type>(done) - it.done; }
	constexpr [[nodiscard]] T& operator*() const { dassert(!done); return *opt; }
	constexpr [[nodiscard]] T* operator->() const { dassert(!done); return opt; }
	constexpr [[nodiscard]] T& operator[](difference_type n) { return *(*this + n); }
	constexpr [[nodiscard]] bool operator==(const optional_iterator& it) const noexcept { return cmp<equal_to>(it); }
	constexpr [[nodiscard]] bool operator!=(const optional_iterator& it) const noexcept { return cmp<not_equal_to>(it); }
	constexpr [[nodiscard]] bool operator<(const optional_iterator& it) const noexcept { return cmp<less>(it); }
	constexpr [[nodiscard]] bool operator<=(const optional_iterator& it) const noexcept { return cmp<less_equal>(it); }
	constexpr [[nodiscard]] bool operator>(const optional_iterator& it) const noexcept { return cmp<greater>(it); }
	constexpr [[nodiscard]] bool operator>=(const optional_iterator& it) const noexcept { return cmp<greater_equal>(it); }
};*/

template<class> struct is_istrm: public false_type {};
template<class C, class Tr> struct is_istrm<basic_istream<C, Tr>>: public true_type {};
template<class S> concept istrm = is_istrm<S>::value;
template<class> struct is_ostrm: public false_type {};
template<class C, class Tr> struct is_ostrm<basic_ostream<C, Tr>>: public true_type {};
template<class S> concept ostrm = is_ostrm<S>::value;
template<class T> struct tuple_like_helper
{
	template<class U> static auto f(U*) -> bool_constant<sizeof(U) == sizeof(U)>;
	static false_type f(...);
	using type = decltype(f((tuple_size<T>*)nullptr));
};
template<class T> concept tuple_like = tuple_like_helper<remove_reference_t<T>>::type::value;
template<class R, class S> concept readable_range = !tuple_like<R> && ranges::range<R> && ranges::output_range<R, ranges::range_value_t<R>>&& istrm<S>&& requires(S& is, ranges::iterator_t<R> it) { {is >> *it} -> same_as<S&>; };
template<class R, class S> concept writable_range = !tuple_like<R> && ranges::input_range<R> && ostrm<S> && requires(S & os, ranges::iterator_t<R> it) { {os << *it} -> same_as<S&>; };

template<class T> [[nodiscard]] T read(istrm auto& is) { T x; is >> x; return x; }
auto& operator>>(istrm auto& is, tuple_like auto&& x) { return apply([&](auto&&... ts) -> auto& { return (is >> ... >> ts); }, x); }
auto& operator<<(ostrm auto& os, tuple_like auto&& x) { return apply([&](auto&&... ts) -> auto& { return (os << ... << ts); }, x); }
template<class T> auto& operator>>(istrm auto& is, optional<T>&& o) { o.emplace(read<T>(is)); return is; }
template<class T> auto& operator<<(ostrm auto& os, optional<T>&& o) { if (o) os << *o; return os; }
template<istrm S> S& operator>>(S& is, readable_range<S> auto&& r) { for (auto it = begin(r); it != end(r); ++it) is >> *it; return is; }
template<ostrm S> S& operator<<(S& os, writable_range<S> auto&& r) { for (auto it = begin(r); it != end(r); ++it) os << *it; return os; }

// Allows reading bitstrings without whitespace
auto& operator>>(istrm auto& is, vector<bool>& r) { for (auto it = begin(r); it != end(r); it++) *it = read<char>(is) == '1'; return is; }

// Doesn't read the current value until dereferencing or advancing past it.
// Works with copy_n etc. but not copy etc. since no end iterator exists.
template<class T, class C = char, class Tr = char_traits<C>, class D = ptrdiff_t> class lazy_istream_iterator
{
public:
	using iterator_category = input_iterator_tag;
	using value_type = T;
	using difference_type = D;
	using pointer = const T*;
	using reference = const T&;
	using char_type = C;
	using traits_type = Tr;
	using istream_type = basic_istream<C, Tr>;
private:
	istream_type& is;
	mutable optional<T> cache;
public:
	constexpr lazy_istream_iterator(basic_istream<C, Tr>& is): is(is) {}
	[[nodiscard]] const T& operator*() const { if (!cache) cache = read<T>(is); return *cache; }
	[[nodiscard]] const T* operator->() const { return &**this; }
	lazy_istream_iterator& operator++() { if (!cache) ignore = read<T>(is); cache.reset(); return *this; }
	[[nodiscard]] lazy_istream_iterator operator++(int) { if (!cache) cin >> cache; lazy_istream_iterator cur(is); swap(cur.cache, cache); return cur; }
};

template<class T>
using os_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
// TODO map typedefs

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

// Compatibility with ICPC notebook code
// all and rall excluded since all conflicts with std::ranges::views::all in C++20
#define rep(i, a, b) for (decltype(a + b) i = (a); i < (b); i++)
#define rrep(i, a, b) for (decltype(a + b) i = (b) - 1; i >= (a); i--)
#define srep(i, a, b, s) for (decltype(a + b + s) i = (a); i < (b); i += (s))
#define srrep(i, a, b, s) for (decltype(a + b + s) i = (b) - 1; i >= (a); i -= (s))
typedef long long ll;
typedef pi32 pii;
typedef a2i32 aii;
typedef vi32 vi;
typedef vvi32 vvi;
typedef vi64 vll;
typedef vbl vb;
mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());

// C++20-specific
#if __cplusplus >= 202002L
namespace std::ranges
{
template<input_or_output_iterator I,
	subrange_kind K = sized_sentinel_for<I, I> ? subrange_kind::sized : subrange_kind::unsized>
subrange<I, I, K> subrange_n(I it, typename iterator_traits<I>::difference_type n)
{
	return subrange(it, it + n, n);
}
}

namespace rng = std::ranges;
namespace vws = std::views;
#endif

// Settings Macros:
#define T_CASES
//#define PRECOMP
//#define PT_NUMS
//#define INTRCTV

#ifdef PRECOMP
void pre();
#endif // PRECOMP
void go();

int main(int argc, const char* argv[])
{
#ifndef INTRCTV
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
#endif // INTRCTV

	ios_base::sync_with_stdio(0);
	cin.tie(0);

#ifdef PRECOMP
	pre();
#endif // PRECOMP

#ifdef T_CASES
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++)
	{
#ifdef PT_NUMS
		cout << "Case #" << tt << ": ";
#endif // PT_NUMS
		go();
	}
#else
	go();
#endif // T_CASES
}

#endif // TEMPLATE_H_INCLUDED

void go()
{
	int n;
	cin >> n;
	vi32 A(n);
	cin >> A;
	for (int& a : A) a--;
	int l = 0, r = n - 1;
	int a = 0, b = n - 1;
	while (l <= r)
	{
		if (A[l] == a)
		{
			l++;
			a++;
		}
		else if (A[l] == b)
		{
			l++;
			b--;
		}
		else if (A[r] == a)
		{
			r--;
			a++;
		}
		else if (A[r] == b)
		{
			r--;
			b--;
		}
		else
			break;
	}
	if (l > r) cout << -1 << endl;
	else cout << l + 1 << ' ' << r + 1 << endl;
}