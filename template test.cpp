//#include "reference/new template.h"

#include <bits/stdc++.h>
using namespace std;

// Rebind
template<class C> struct rebind;
template<class C, class T> using rebind_t = typename rebind<C>::type<T>;
template<template<class, class...> class M, class T, class... Args> struct rebind<M<T, Args...>> { template<class U> using type = M<U, Args...>; };
template<class T, size_t S> struct rebind<array<T, S>> { template<class U> using type = array<U, S>; };
template<class T> struct rebind<T*> { template<class U> using type = U*; };

// Example Iterator
struct example_iter
{
	using iterator_concept = std::contiguous_iterator_tag;
	using difference_type = ptrdiff_t;
	using value_type = int;
	using pointer = value_type*;
	using reference = value_type&;
};

// iterator_interface
template<class It, class Cat, class T, class D = ptrdiff_t, class P = D*, class R = D&>
struct iterator_interface
{

};



// Needs value_type, monad_type, rebind, unit, and bind
template<class> struct monad_traits;

template<class F, class M, class T = typename monad_traits<M>::value_type>
concept monad_bindable = same_as<typename monad_traits<invoke_result_t<F, T>>::rebind<T>, M>;

// Derived classes need to implement unit and bind themselves
template<class M, class T, template<class> class R = rebind<M>::type> struct monad_traits_interface
{
	using value_type = T;
	using monad_type = M;
	template<class U> using rebind = R<U>;
};

template<template<class, class...> class C, class T, class... Args>
struct monad_traits_container: public monad_traits_interface<C<T, Args...>, T>
{
	[[nodiscard]] static constexpr monad_type unit(T&& t) { return { forward<T>(t) }; }

};

template<class T>
struct monad_traits<optional<T>>
{
	using value_type = T;
	using monad_type = optional<T>;
	template<class U>
	using rebind = optional<U>;
	[[nodiscard]] static constexpr monad_type unit(T&& t) { return { forward<T>(t) }; }
	template<monad_bindable<monad_type> F>
	[[nodiscard]] static constexpr invoke_result_t<F, T> bind(monad_type&& m, F&& f)
	{
		return m.has_value() ? nullopt : forward<F>(f)(forward<T>(m));
	}
};

template<class T, class A>
struct monad_traits<vector<T, A>>
{
	using value_type = T;
	using monad_type = vector<T, A>;
	template<class U>
	using rebind = vector<U, A>;
	[[nodiscard]] static constexpr monad_type unit(T&& t) { return { forward<T>(t) }; }
	template<class F, monad_bindable<monad_type, F> = nullptr>
	[[nodiscard]] static constexpr invoke_result_t<F, T> bind(monad_type&& m, F&& f)
	{
		invoke_result_t<F, T> ans, cur;
		for (T& t : m)
		{
			cur = forward<F>(f)(forward<T>(t));
			ans.reserve(size(ans) + size(cur));
			move(begin(cur), end(cur), back_inserter(ans));
		}
		return ans;
	}
};
/*template<class T, class A> struct monad_traits<vector<T, A>>
{
	using value_type = T;
	using monad_type = vector<T, A>;
	template<class U> using rebind = vector<U, A>;
	static monad_type unit(T&& t) { return monad_type{ forward<T>(t); } }
	template<class U> static rebind<U> bind(monad_type&& m, )
}*/

template<class M>
[[nodiscard]] constexpr M unit(typename monad_traits<M>::value_type&& a) { return monad_traits<M>::unit(forward<decltype(a)>(a)); }
template<class M, class F>
[[nodiscard]] constexpr invoke_result_t<F, typename monad_traits<M>::value_type> bind(M&& m, F&& f) { return monad_traits<M>::bind(forward<M>(m), forward<F>(f)); }
template<class M, class F>
[[nodiscard]] constexpr invoke_result_t<F, typename monad_traits<M>::value_type> operator>>=(M&& m, F&& f) { return bind(forward<M>(m), forward<F>(f)); }
//template<template<class> class M, class F>

//template<template<class> class M> is_

//template<template<class> class M> struct monad_traits;

/*
template<> struct monad_traits<type_identity_t>
{
	template<class T> using monad = type_identity_t<T>;
	template<class T> monad<T> unit(T&& t) { return t; }
	template<class T, class F> bind(monad<T>&& m, F&& f) { return forward<F>(f)(forward<monad<T>>(m)); }
};
template<> struct monad_traits<optional>
{
	template<class T> using monad = optional<T>;
	template<class T> monad<T> unit(T&& t) { return { forward<T>(t) }; }
	template<class T, class F> auto bind(monad<T>&& m, F&& f) { return forward<F>(f)(forward<monad<T>>(m)); }
};
template<> struct monad_traits*/

vector<size_t> upto(size_t x)
{
	vector<size_t> ans(x);
	iota(begin(ans), end(ans), (size_t)0);
	return ans;
}

void go()
{
	optional<int> x = nullopt, y = unit<optional<int>>(4);

	cout << x.value_or(-1) << ' ' << y.value_or(-1) << endl;

	for (auto i : upto(14) >>= &upto)
		cout << i << ' ';
	cout << endl;
}

int main()
{
	go();
}