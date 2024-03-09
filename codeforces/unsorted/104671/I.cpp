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
namespace pbds = __gnu_pbds;

// TODO fix tuple hashing
template<size_t S, class... Ts>
struct TupleHashHelper
{
	typedef std::tuple<Ts...> Tup;
	typedef TupleHashHelper<S - 1, Ts...> Helper;
	typedef std::tuple_element_t<S - 1, Tup> T;
	inline constexpr size_t operator()(const Tup &t) const noexcept
	{
		return (size_t)31 * Helper()(t) + std::hash<T>()(std::get<S - 1>(t));
	}
};

template<class... Ts>
struct TupleHashHelper<0, Ts...>
{
	typedef std::tuple<Ts...> Tup;
	inline constexpr size_t operator()(const Tup &) const noexcept
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
	inline constexpr size_t operator()(const Tup &t) const noexcept
	{
		return Helper()(t);
	}
};

template<class T, class U>
struct std::hash<pair<T, U>>
{
	inline constexpr size_t operator()(const pair<T, U> &p) const noexcept
	{
		return (size_t)31 * hash<T>()(p.first) + hash<U>()(p.second);
	}
};

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

template<class> struct is_istrm : public false_type {};
template<class C, class Tr> struct is_istrm<basic_istream<C, Tr>> : public true_type {};
template<class S> concept istrm = is_istrm<S>::value;
template<class> struct is_ostrm : public false_type {};
template<class C, class Tr> struct is_ostrm<basic_ostream<C, Tr>> : public true_type {};
template<class S> concept ostrm = is_ostrm<S>::value;
template<class T> struct tuple_like_helper
{
	template<class U> static bool_constant<sizeof(U) == sizeof(U)> f(U *);
	static false_type f(...);
	using type = decltype(f((tuple_size<T> *)nullptr));
};
template<class T> concept tuple_like = tuple_like_helper<remove_reference_t<T>>::type::value;
template<class R, class S> concept read_as_range = !tuple_like<R> && ranges::range<R> && ranges::output_range<R, ranges::range_value_t<R>> &&istrm<S> &&requires(S &is, ranges::iterator_t<R> it) { {is >> *it} -> same_as<S &>; };
template<class R, class S> concept write_as_range = !tuple_like<R> && ranges::input_range<R> && ostrm<S> && requires(S & os, ranges::iterator_t<R> it) { {os << *it} -> same_as<S &>; };

template<class T> [[nodiscard]] T read(istrm auto &is) { T x; is >> x; return x; }
auto &operator>>(istrm auto &is, tuple_like auto &&x) { return apply([&](auto&&... ts) -> auto & { return (is >> ... >> ts); }, x); }
auto &operator<<(ostrm auto &os, tuple_like auto &&x) { return apply([&](auto&&... ts) -> auto & { return (os << ... << ts); }, x); }
template<class T> auto &operator>>(istrm auto &is, optional<T> &&o) { o.emplace(read<T>(is)); return is; }
template<class T> auto &operator<<(ostrm auto &os, optional<T> &&o) { if (o) os << *o; return os; }
template<istrm S> S &operator>>(S &is, read_as_range<S> auto &&r) { for (auto it = begin(r); it != end(r); ++it) is >> *it; return is; }
template<ostrm S> S &operator<<(S &os, write_as_range<S> auto &&r) { for (auto it = begin(r); it != end(r); ++it) os << *it; return os; }

// Allows reading bitstrings without whitespace
auto &operator>>(istrm auto &is, vector<bool> &r) { for (auto it = begin(r); it != end(r); it++) *it = read<char>(is) == '1'; return is; }

template<template<class...> class C, class... Args> concept template_constructible_from = requires { C(declval<Args>()...);};

// TODO more constructors
/*
template<class T, size_t S>
struct rarray
{
	using array_type = std::array<T, S>;
	using value_type = array_type::value_type;
	using size_type = array_type::size_type;
	using difference_type = array_type::difference_type;
	using reference = array_type::reference;
	using const_reference = array_type::const_reference;
	using pointer = array_type::pointer;
	using const_pointer = array_type::const_pointer;
	using iterator = array_type::iterator;
	using const_iterator = array_type::const_iterator;
	using reverse_iterator = array_type::reverse_iterator;
	using const_reverse_iterator = array_type::const_reverse_iterator;
	array_type a;
	[[nodiscard]] constexpr auto& at(size_t pos) { return a.at(pos); }
	[[nodiscard]] constexpr const auto& at(size_t pos) const { return a.at(pos); }
	[[nodiscard]] constexpr auto& operator[](size_t pos) { return a[pos]; }
	[[nodiscard]] constexpr const auto& operator[](size_t pos) const { return a[pos]; }
	[[nodiscard]] constexpr auto& front() { return a.front(); }
	[[nodiscard]] constexpr const auto& front() const { return a.front(); }
	[[nodiscard]] constexpr auto& back() { return a.back(); }
	[[nodiscard]] constexpr const auto& back() const { return a.back(); }
	[[nodiscard]] constexpr auto data() { return a.data(); }
	[[nodiscard]] constexpr auto data() const { return a.data(); }
	[[nodiscard]] constexpr auto begin() noexcept { return a.begin(); }
	[[nodiscard]] constexpr auto begin() const noexcept { return a.begin(); }
	[[nodiscard]] constexpr auto cbegin() const noexcept { return a.cbegin(); }
	[[nodiscard]] constexpr auto end() noexcept { return a.end(); }
	[[nodiscard]] constexpr auto end() const noexcept { return a.end(); }
	[[nodiscard]] constexpr auto cend() const noexcept { return a.cend(); }
	[[nodiscard]] constexpr auto rbegin() noexcept { return a.rbegin(); }
	[[nodiscard]] constexpr auto rbegin() const noexcept { return a.rbegin(); }
	[[nodiscard]] constexpr auto crbegin() const noexcept { return a.crbegin(); }
	[[nodiscard]] constexpr auto rend() noexcept { return a.rend(); }
	[[nodiscard]] constexpr auto rend() const noexcept { return a.rend(); }
	[[nodiscard]] constexpr auto crend() const noexcept { return a.crend(); }
	[[nodiscard]] constexpr auto size() const noexcept { return a.size(); }
	[[nodiscard]] constexpr auto empty() const noexcept { return a.empty(); }
	constexpr void fill(const T& t) { a.fill(t); }
	constexpr void swap(rarray& y) noexcept(noexcept(a.swap(y.a))) { a.swap(y.a); }
	constexpr friend void swap(rarray& x, rarray& y) noexcept(noexcept(x.swap(y))) { swap(x.a, y.a); }
	[[nodiscard]] constexpr rarray() = default;
	[[nodiscard]] constexpr rarray(array_type&& a) noexcept: a(forward<array_type>(a)) {}
	template<input_iterator It> [[nodiscard]] constexpr rarray(It first, It last)
	{
		for (auto it = begin(); it != end(); it++)
		{
			dassert(first != last);
			*it = forward<T>(*first++);
		}
		dassert(first == last);
	}
	constexpr operator const array_type& () const { return a; }
	constexpr operator array_type& () { return a; }
};*/

template<size_t N> struct sarray { template<class T> using type = array<T, N>; };

// Port of std::ranges::to to C++20 based on draft n4910
// TODO specialization for std::array
constexpr struct from_range_t {} from_range;
template<class C> concept reservable_container = ranges::sized_range<C> && requires(C & c, ranges::range_size_t<C> n)
{
	c.reserve(n);
	{ c.capacity() } -> same_as<decltype(n)>;
	{ c.max_size() } -> same_as<decltype(n)>;
};
template<class C, class R> concept container_insertable = requires (C & c, R && r)
{
	requires (requires { c.push_back(forward<R>(r)); } || requires { c.insert(c.end(), forward<R>(r)); });
};
template<class R, class C> constexpr auto container_inserter(C &c)
{
	if constexpr (requires { c.push_back(declval<R>()); })
		return back_inserter(c);
	else
		return inserter(c, c.end());
}
template<class C, ranges::input_range R, class... Args> requires (!ranges::view<C>) struct to_helper_1
{
	constexpr C operator()(R &&r, Args&&... args) const
	{
		if constexpr (!ranges::input_range<C> || convertible_to<ranges::range_reference_t<R>, ranges::range_value_t<C>>)
		{
			if constexpr (constructible_from<C, R, Args...>)
				return C(forward<R>(r), forward<Args>(args)...);
			else if constexpr (constructible_from<C, from_range_t, R, Args...>)
				return C(from_range, forward<R>(r), forward<Args>(args)...);
			else if constexpr (ranges::common_range<R>
				&& derived_from<typename iterator_traits<ranges::iterator_t<R>>::iterator_category, input_iterator_tag>
				&& constructible_from<C, ranges::iterator_t<R>, ranges::sentinel_t<R>, Args...>)
				return C(ranges::begin(r), ranges::end(r), forward<Args>(args)...);
			else
			{
				C c(forward<Args>(args)...);
				if constexpr (ranges::sized_range<R> && reservable_container<C>)
					c.reserve(static_cast<ranges::range_size_t<C>>(ranges::size(r)));
				ranges::copy(r, container_inserter<ranges::range_reference_t<R>>(c));
				return c;
			}
		}
		else
			return to<C>(r | views::transform([](auto &&elem)
				{
					return to<ranges::range_value_t<C>>(std::forward<decltype(elem)>(elem));
				}), std::forward<Args>(args)...);
	}
};
template<class T, size_t N, ranges::input_range R> struct to_helper_1<array<T, N>, R> // Nonstandard
{
	constexpr array<T, N> operator()(R &&r) const
	{
		array<T, N> c{};
		auto it = ranges::copy(r, ranges::begin(c)).out;
		dassert(it - begin(c) == N);
		return c;
	}
};
template<class C, ranges::input_range R, class... Args> requires (!ranges::view<C>) constexpr C to(R &&r, Args&&... args)
{
	return to_helper_1<C, R, Args...>()(forward<R>(r), forward<Args>(args)...);
}
template<size_t N, ranges::input_range R> constexpr auto to(R &&r) // Nonstandard
{
	return to<array<ranges::range_value_t<R>, N>>(forward<R>(r));
}
template<template<class...> class C, ranges::input_range R, class... Args> constexpr auto to(R &&r, Args&&... args)
{
	struct input_iterator
	{
		using iterator_category [[maybe_unused]] = input_iterator_tag;
		using value_type [[maybe_unused]] = ranges::range_value_t<R>;
		using difference_type [[maybe_unused]] = ptrdiff_t;
		using pointer [[maybe_unused]] = add_pointer_t<ranges::range_reference_t<R>>;
		using reference [[maybe_unused]] = ranges::range_reference_t<R>;
		reference operator*() const;
		pointer operator->() const;
		input_iterator &operator++();
		input_iterator operator++(int);
		bool operator==(const input_iterator &) const;
	};
	if constexpr (template_constructible_from<C, R, Args...>) return to<decltype(C(declval<R>(), declval<Args>()...))>(forward<R>(r), forward<Args>(args)...);
	else if constexpr (template_constructible_from<C, from_range_t, R, Args...>) return to<decltype(C(from_range, declval<R>(), declval<Args>()...))>(forward<R>(r), forward<Args>(args)...);
	else return to<decltype(C(declval<input_iterator>(), declval<input_iterator>(), declval<Args>()...))>(forward<R>(r), forward<Args>(args)...);
}
// Based loosely on libstdc++'s std::bind_front implementation
template<class C, class... Args> struct To1
{
private:
	using I = index_sequence_for<Args...>;
	tuple<Args...> b;
	template<class S, size_t... I, ranges::range R> static constexpr C call(S &&s, index_sequence<I...>, R &&r) { return to<C, R, Args...>(forward<R>(r), get<I>(forward<S>(s).b)...); }
public:
	template<class... A> explicit constexpr To1(int, A&&... a) noexcept((is_nothrow_constructible_v<Args, A> && ...)) : b(forward<A>(a)...) { static_assert(sizeof...(Args) == sizeof...(A)); }
	template<ranges::range R> constexpr C operator()(R &&r) & { return call(*this, I(), forward<R>(r)); }
	template<ranges::range R> constexpr C operator()(R &&r) const & { return call(*this, I(), forward<R>(r)); }
	template<ranges::range R> constexpr C operator()(R &&r) && { return call(move(*this), I(), forward<R>(r)); }
	template<ranges::range R> constexpr C operator()(R &&r) const && { return call(move(*this), I(), forward<R>(r)); }
};
template<size_t N> struct To2
{
private:
	template<class S, ranges::range R> static constexpr auto call(S &&s, R &&r) { return to<N>(forward<R>(r)); }
public:
	template<ranges::range R> constexpr auto operator()(R &&r) & { return call(*this, forward<R>(r)); }
	template<ranges::range R> constexpr auto operator()(R &&r) const & { return call(*this, forward<R>(r)); }
	template<ranges::range R> constexpr auto operator()(R &&r) && { return call(move(*this), forward<R>(r)); }
	template<ranges::range R> constexpr auto operator()(R &&r) const && { return call(move(*this), forward<R>(r)); }
};
template<template<class...> class C, class... Args> struct To3
{
private:
	using I = index_sequence_for<Args...>;
	tuple<Args...> b;
	template<class S, size_t... I, ranges::range R> static constexpr auto call(S &&s, index_sequence<I...>, R &&r) { return to<C, R, Args...>(forward<R>(r), get<I>(forward<S>(s).b)...); }
public:
	template<class... A> explicit constexpr To3(int, A&&... a) noexcept((is_nothrow_constructible_v<Args, A> && ...)) : b(forward<A>(a)...) { static_assert(sizeof...(Args) == sizeof...(A)); }
	template<ranges::range R> constexpr auto operator()(R &&r) & { return call(*this, I(), forward<R>(r)); }
	template<ranges::range R> constexpr auto operator()(R &&r) const & { return call(*this, I(), forward<R>(r)); }
	template<ranges::range R> constexpr auto operator()(R &&r) && { return call(move(*this), I(), forward<R>(r)); }
	template<ranges::range R> constexpr auto operator()(R &&r) const && { return call(move(*this), I(), forward<R>(r)); }
};
template<class C, class... Args> requires (!ranges::view<C>) constexpr auto to(Args&&... args) { return To1<C, Args...>(0, forward<Args>(args)...); }
template<size_t N> constexpr auto to() { return To2<N>(0); }
template<template<class...> class C, class... Args> constexpr auto to(Args&&... args) { return To3<C, Args...>(0, forward<Args>(args)...); }

// Doesn't read the current value until dereferencing or advancing past it.
// Works with copy_n etc. but not copy etc. since no end iterator exists.
template<class T, class C = char, class Tr = char_traits<C>, class D = ptrdiff_t> class lazy_istream_iterator
{
public:
	using iterator_category = input_iterator_tag;
	using value_type = T;
	using difference_type = D;
	using pointer = const T *;
	using reference = const T &;
	using char_type = C;
	using traits_type = Tr;
	using istream_type = basic_istream<C, Tr>;
private:
	istream_type &s;
	mutable optional<T> cache;
public:
	constexpr lazy_istream_iterator(basic_istream<C, Tr> &is) : s(is) {}
	[[nodiscard]] const T &operator*() const { if (!cache) cache = read<T>(s); return *cache; }
	[[nodiscard]] const T *operator->() const { return &**this; }
	lazy_istream_iterator &operator++() { if (!cache) ignore = read<T>(s); cache.reset(); return *this; }
	[[nodiscard]] lazy_istream_iterator operator++(int) { if (!cache) s >> cache; lazy_istream_iterator cur(s); swap(cur.cache, cache); return cur; }
};
// Iterate over set bits of an integer
// TODO Maybe specialize for bitset
template<integral T> class biterator
{
private:
	using U = make_unsigned_t<T>;
	static constexpr T BITS = sizeof(T) * CHAR_BIT;
	T a = 0, b = 0; // Unused, used bits
	static constexpr int lo_idx(T t) { return countr_zero<U>(t); }
	static constexpr int hi_idx(T t) { return BITS - countl_zero<U>(t); }
	constexpr T a_lo() const { return a & -a; }
	constexpr T b_hi() const { return T(1) << hi_idx(b); }
	constexpr void sw(T bit) { a ^= bit; b ^= bit; }
	template<template<class> class C> constexpr auto cmp(const biterator &it) const noexcept { return C<T>()(it.a, a); }
public:
	using value_type = int;
	using difference_type = int;
	using pointer = int *;
	using const_pointer = int *;
	using reference = int;
	using const_reference = int;
	using iterator_category = bidirectional_iterator_tag;
	using iterator_concept = bidirectional_iterator_tag;
	constexpr biterator() noexcept = default;
	constexpr biterator(T val) noexcept : a(val) {}
	constexpr biterator &operator++() noexcept { dassert(a); sw(a_lo()); return *this; }
	constexpr biterator &operator--() noexcept { dassert(b); sw(b_hi()); return *this; }
	[[nodiscard]] constexpr biterator operator++(int) noexcept { auto it = *this; ++*this; return it; }
	[[nodiscard]] constexpr biterator operator--(int) noexcept { auto it = *this; --*this; return it; }
	[[nodiscard]] constexpr int idx() const noexcept { return lo_idx(a); }
	[[nodiscard]] constexpr T bit() const noexcept { return a_lo(); }
	[[nodiscard]] constexpr pair<int, T> operator*() const noexcept { dassert(a); return { idx(), bit() }; }
	[[nodiscard]] constexpr bool operator==(const biterator &it) const noexcept { return cmp<equal_to>(it); }
	[[nodiscard]] constexpr bool operator!=(const biterator &it) const noexcept { return cmp<not_equal_to>(it); }
	[[nodiscard]] constexpr bool operator<(const biterator &it) const noexcept { return cmp<less>(it); }
	[[nodiscard]] constexpr bool operator<=(const biterator &it) const noexcept { return cmp<less_equal>(it); }
	[[nodiscard]] constexpr bool operator>(const biterator &it) const noexcept { return cmp<greater>(it); }
	[[nodiscard]] constexpr bool operator>=(const biterator &it) const noexcept { return cmp<greater_equal>(it); }
	[[nodiscard]] constexpr strong_ordering operator<=>(const biterator &it) const noexcept { return cmp<compare_three_way>(it); }
};

template<integral T> struct bits : public ranges::view_interface<bits<T>>
{
	T x;
	[[nodiscard]] constexpr bits(T val = 0) : x(val) {}
	[[nodiscard]] constexpr biterator<T> begin() { return biterator<T>(x); }
	[[nodiscard]] constexpr biterator<T> end() { return biterator<T>(); }
};

template<class T>
using os_set = pbds::tree<T, pbds::null_type, less<T>, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

template<integral T> [[nodiscard]] constexpr T rup2(T x) noexcept
{
	if (x-- == 0) return 1;
	for (int i = 1; i < int(CHAR_BIT * sizeof(T)); i *= 2) x |= x >> i;
	return ++x;
}
template<unsigned_integral T> [[nodiscard]] constexpr T isqrtc(T x)
{
	T ub = ((T)1 << (8 * sizeof(x) - countl_zero(x) + 1) / 2) + 1;
	return *ranges::lower_bound(views::iota((T)0, ub), x, {}, [](T r) { return r * r; });
}
template<signed_integral T> [[nodiscard]] constexpr T isqrtc(T x)
{
	return isqrtc<make_unsigned_t<T>>(x);
}
template<unsigned_integral T> [[nodiscard]] constexpr T isqrtf(T x)
{
	T r = isqrtc(x);
	return r - (r * r != x);
}
template<signed_integral T> [[nodiscard]] constexpr T isqrtf(T x)
{
	return isqrtf<make_unsigned_t<T>>(x);
}
template<uint64_t N> constexpr uint32_t ISQRTC = static_cast<uint32_t>(isqrtc(N));
template<uint64_t N> constexpr uint32_t ISQRTF = ISQRTC<N> -(ISQRTC<N> *ISQRTC<N> != N);

[[nodiscard]] constexpr uint32_t phi(uint32_t a)
{
	uint32_t phi = a;
	for (uint32_t i = 2; (uint64_t)i * i <= a; i++)
	{
		if (a % i) continue;
		phi = phi / i * (i - 1);
		do a /= i; while (a % i == 0);
	}
	return a < 2 ? phi : phi / a * (a - 1);
}
template<uint32_t a> constexpr uint32_t PHI = phi(a);
template<uint32_t a> constexpr bool PRIME = PHI<a> +1 == a;

template<uint32_t M> struct mint
{
	static_assert(0 < M);
	static_assert(M < 1u << 31);

	constexpr static uint32_t MOD = M;
	constexpr static uint32_t PHI = PHI<M>;
	constexpr static bool PRIME = PRIME<M>;
	using pow_t = mint<PHI>;
	constexpr static pow_t INV_POW = M - 2;

	uint32_t v;

	constexpr mint() = default;
	constexpr mint(integral auto u) : v(static_cast<uint32_t>(u < 0 ? u % M + M : u % M)) { if (v == M) v = 0; }
	[[nodiscard]] constexpr uint32_t val() const { return v; }
	constexpr mint &operator++() { if (++v == M) v = 0; return *this; }
	[[nodiscard]] constexpr mint operator++(int) { mint a = *this; ++*this; return a; }
	constexpr mint &operator--() { if (v-- == 0) v = M - 1; return *this; }
	[[nodiscard]] constexpr mint operator--(int) { mint a = *this; --*this; return a; }
	[[nodiscard]] constexpr friend mint operator+(mint a) { return a; }
	[[nodiscard]] constexpr friend mint operator-(mint a) { if (a.v) a.v = M - a.v; return a; }
	constexpr mint &operator+=(mint b) { if ((v += b.v) >= M) v -= M; return *this; }
	constexpr mint &operator+=(integral auto b) { return *this += mint(b); }
	[[nodiscard]] constexpr friend mint operator+(mint a, mint b) { return a += b; }
	[[nodiscard]] constexpr friend mint operator+(mint a, integral auto b) { return a + mint(b); }
	[[nodiscard]] constexpr friend mint operator+(integral auto a, mint b) { return mint(a) + b; }
	constexpr mint &operator-=(mint b) { if ((v += M - b.v) >= M) v -= M; return *this; }
	constexpr mint &operator-=(integral auto b) { return *this -= mint(b); }
	[[nodiscard]] constexpr friend mint operator-(mint a, mint b) { return a -= b; }
	[[nodiscard]] constexpr friend mint operator-(mint a, integral auto b) { return a - mint(b); }
	[[nodiscard]] constexpr friend mint operator-(integral auto a, mint b) { return mint(a) - b; }
	constexpr mint &operator*=(mint b) { v = uint32_t((uint64_t)v * b.v % M); return *this; }
	constexpr mint &operator*=(integral auto b) { return *this *= mint(b); }
	[[nodiscard]] constexpr friend mint operator*(mint a, mint b) { return a *= b; }
	[[nodiscard]] constexpr friend mint operator*(mint a, integral auto b) { return a * mint(b); }
	[[nodiscard]] constexpr friend mint operator*(integral auto a, mint b) { return mint(a) * b; }
	[[nodiscard]] constexpr friend mint mpow(mint a, pow_t b)
	{
		mint p = 1;
		for (; b.v; b.v /= 2, a *= a) if (b.v % 2) p *= a;
		return p;
	}
	[[nodiscard]] constexpr friend mint mpow(mint a, integral auto b) { return mpow(a, pow_t(b)); }
	[[nodiscard]] constexpr mint pow(pow_t b) const { return mpow(*this, b); }
	[[nodiscard]] constexpr mint pow(integral auto b) const { return mpow(*this, pow_t(b)); }
	[[nodiscard]] constexpr mint inv() const requires PRIME
	{
		dassert(*this);
		return mpow(*this, INV_POW);
	}
	[[nodiscard]] constexpr friend mint minv(mint a) requires PRIME { return a.inv(); }
	constexpr mint &operator/=(mint b) requires PRIME { return *this *= b.inv(); }
	constexpr mint &operator/=(integral auto b) requires PRIME { return *this /= mint(b); }
	[[nodiscard]] constexpr friend mint operator/(mint a, mint b) requires PRIME { return a /= b; }
	[[nodiscard]] constexpr friend mint operator/(mint a, integral auto b) requires PRIME { return a / mint(b); }
	[[nodiscard]] constexpr friend mint operator/(integral auto a, mint b) requires PRIME { return mint(a) / b; }
	[[nodiscard]] constexpr friend bool operator==(mint a, mint b) { return a.v == b.v; }
	[[nodiscard]] constexpr friend bool operator==(mint a, integral auto b) { return a == mint(b); }
	[[nodiscard]] constexpr friend bool operator==(integral auto a, mint b) { return mint(a) == b; }
	[[nodiscard]] constexpr friend bool operator!=(mint a, mint b) { return a.v != b.v; }
	[[nodiscard]] constexpr friend bool operator!=(mint a, integral auto b) { return a != mint(b); }
	[[nodiscard]] constexpr friend bool operator!=(integral auto a, mint b) { return mint(a) != b; }
	[[nodiscard]] constexpr friend bool operator<(mint a, mint b) { return a.v < b.v; }
	[[nodiscard]] constexpr friend bool operator<(mint a, integral auto b) { return a < mint(b); }
	[[nodiscard]] constexpr friend bool operator<(integral auto a, mint b) { return mint(a) < b; }
	[[nodiscard]] constexpr friend bool operator<=(mint a, mint b) { return a.v <= b.v; }
	[[nodiscard]] constexpr friend bool operator<=(mint a, integral auto b) { return a <= mint(b); }
	[[nodiscard]] constexpr friend bool operator<=(integral auto a, mint b) { return mint(a) <= b; }
	[[nodiscard]] constexpr friend bool operator>(mint a, mint b) { return a.v > b.v; }
	[[nodiscard]] constexpr friend bool operator>(mint a, integral auto b) { return a > mint(b); }
	[[nodiscard]] constexpr friend bool operator>(integral auto a, mint b) { return mint(a) > b; }
	[[nodiscard]] constexpr friend bool operator>=(mint a, mint b) { return a.v >= b.v; }
	[[nodiscard]] constexpr friend bool operator>=(mint a, integral auto b) { return a >= mint(b); }
	[[nodiscard]] constexpr friend bool operator>=(integral auto a, mint b) { return mint(a) >= b; }
	[[nodiscard]] constexpr operator uint32_t() const { return v; }
	friend istream &operator>>(istream &istrm, mint &a) { intmax_t v; istrm >> v; a = v; return istrm; }
	friend ostream &operator<<(ostream &ostrm, mint a) { return ostrm << a.v; }
};

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
TDEFS1(string);
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
#define rep(i, a, b) for (decltype((a) + (b)) i = (a); i < (b); ++i)
#define rrep(i, a, b) for (decltype((a) + (b)) i = (b) - 1; i >= (a); --i)
#define srep(i, a, b, s) for (decltype((a) + (b) + s) i = (a); i < (b); i += (s))
#define srrep(i, a, b, s) for (decltype((a) + (b) + s) i = (b) - 1; i >= (a); i -= (s))
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

namespace views = ranges::views;
#endif

// Settings Macros:
//#define T_CASES
//#define PRECOMP
//#define PT_NUMS
#define OFFLINE

#ifdef PRECOMP
void pre();
#endif // PRECOMP
void go();

int main(int argc, const char *argv[])
{
#ifdef OFFLINE
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
#endif // OFFLINE

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

// from KACTL
typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M)
{
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod)
{
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool isPrime(ull n)
{
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 },
		s = __builtin_ctzll(n - 1), d = n >> s;
	for (ull a : A)
	{   // ^ count trailing zeroes
		ull p = modpow(a % n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n - 1 && i != s) return 0;
	}
	return 1;
}

ull pollard(ull n)
{
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1)
	{
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n)
{
	if (n == 1) return {};
	if (isPrime(n)) return { n };
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), ALL(r));
	return l;
}
// no longer from KACTL

void go()
{
	int n, q;
	cin >> n >> q;
	vi32 A(n);
	cin >> A;
	ull cnt = 0;
	ull sum = 0;
	set<int> S;
	rep(i, 0, n)
	{
		cnt += A[i];
		sum += A[i] * (i + 1);
		S.insert(i);
	}

	string cmd;
	while (q--)
	{
		cin >> cmd;
		if (cmd == "SET")
		{
			int i, x;
			cin >> i >> x;
			i--;
			cnt -= A[i];
			cnt += x;
			sum -= (ull)A[i] * (i + 1);
			sum += (ull)x * (i + 1);
			A[i] = x;
			if (x == 0)
				S.erase(x);
			else
				S.insert(x);
		}
		else
		{
			ull k;
			cin >> k;
			if (k == sum)
			{
				cout << (cnt % 2 ? "RYAN\n" : "PHEBE\n");
				continue;
			}
			if (k < (ull)*prev(end(S)) || k > sum || (sum - k) % 2 == 1)
			{
				cout << (cnt % 2 ? "PHEBE\n" : "RYAN\n");
				continue;
			}
			ull diff = sum - k;
			vector<ull> F = factor(diff / 2);
			sort(ALL(F));
			vector<pair<int, int>> primes;
			for (int i = 0; i < (int)F.size(); i++)
			{
				if (F[i] > (ull)n)
					continue;
				else if (primes.empty() || F[i] != primes.back().first)
					primes.emplace_back((int)F[i], 1);
				else
					primes.back().second++;
			}
			vector<int> divisors{ 1 };
			for (auto [p, f] : primes)
			{
				int s = (int)size(divisors);
				ull pp = 1;
				rep(i, 0, f)
				{
					pp *= p;
					if (pp > (ull)n)
						break;
					rep(j, 0, s)
						if (pp * divisors[j] <= (ull)n)
							divisors.push_back((int)pp * divisors[j]);
				}
			}

			bool found = false;
			for (int d : divisors)
			{
				ull cd = A[d - 1], cx = cnt - cd;
				ull need = diff / d;
				//cerr << d << ' ' << cd << ' ' << cx << ' ' << need << endl;
				if (need > cd)
					continue;
				cd -= need;
				if (cnt % 2 == 0)
					cd++;
				if (cd >= cx)
				{
					//cerr << " found\n";
					found = true;
					break;
				}
			}
			if (found)
				cout << (cnt % 2 ? "RYAN\n" : "PHEBE\n");
			else
				cout << (cnt % 2 ? "PHEBE\n" : "RYAN\n");
			//cerr << endl;
		}
	}
}
