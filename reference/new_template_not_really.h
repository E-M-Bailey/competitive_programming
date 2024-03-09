#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#ifdef DEBUG
#define DBG(x) (x)
#define dassert(x) assert(x)
#else
#define DBG(x)
#define dassert(x) do {} while (0)
#endif

using namespace std;
using namespace chrono;
using namespace __gnu_pbds;

namespace my
{
template<class D, input_or_output_iterator It>
struct iterator_adapter_interface
{
	
};
template<input_or_output_iterator It>
struct lazy
{
	using iterator_type = It;
	using
		It it;

	template<class... Args>
};
}

/*
template<template<class> class M> struct monad_traits {};

template<> struct monad_traits<type_identity_t>
{
	using monad = type_identity_t;
	template<class T> monad<T> unit(T&& t) { return t; }
	template<class T, class F> bind(monad<T>&& m, F&& f) { return forward<F>(f)(forward<monad<T>>(m)); }
};

template<> struct monad_traits<optional>
{

};*/



/*
// Hash utils
template<class T = void> struct hasher {};
#define INT_HASH(T) template<> struct hasher<T> { constexpr size_t operator()(const T& x) const noexcept { return _Hash_impl::hash(x); } }
#define FLOAT_HASH(T, Z) template<> struct hasher<T> { constexpr size_t operator()(const T& x) const noexcept { return x == -Z ? 0}}
TRIVIAL_HASH(int);
//template<> struct hasher
template<class C, class Tr, class A> struct hasher<basic_string<C, Tr, A>>
{
	constexpr size_t operator()(const basic_string<C, Tr, A>& str) noexcept
	{
		return _Hash_impl::hash()
	}
};


// Based on boost::hash_combine
static constexpr size_t HASH_MAGIC = sizeof(size_t) == 8 ? 0x9e3779b97f4a7c15 : 0x9e3779b9;
template<class... Ts> constexpr size_t variadic_hash(const Ts&... ts) noexcept
{
	size_t h = 0;
	return (h ^= std::hash<Ts>()(ts) + HASH_MAGIC + (h << 6) + (h >> 2), ...);
}

template<class T> struct hash { constexpr size_t operator()(T&& x) const noexcept { return std::hash<T>()(forward<T>(x)); } };

template<class... Ts> struct std::hash<tuple<Ts...>>
{
	constexpr size_t operator()(const)
};

//template<class T>*/

/*template<class It = int*, class Tr = iterator_traits<It>> class lazy_iterator
{
	using iterator_category = Tr::iterator_category;
	using value_type = Tr::value_type;
	using difference_type = Tr::;
	using pointer = const
};*/

// Doesn't read the current value until dereferencing or advancing past it.
// Works with copy_n etc. but not copy etc. since no end iterator exists.
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

// Algebra concepts
//#define ALG_2(name, def) template<class T, class A> constexpr bool name##_v = def; template<class T, class A> using name = bool_constant<name##_v<T, A>>
//ALG_2(bin_op, (is_invocable_r_v<T, A, T, T>));
//ALG_2(bin_op, ())

#endif // TEMPLATE_H_INCLUDED
