
#include "template.h"

constexpr u32 phi(u32 a)
{
	u32 phi = a;
	for (u32 i = 2; (u64)i * i <= a; i++)
	{
		if (a % i) continue;
		phi = phi / i * (i - 1);
		do a /= i; while (a % i == 0);
	}
	return a < 2 ? phi : phi / a * (a - 1);
}
constexpr bool prime(u32 a) { return phi(a) + 1 == a; }
template<u32 a> constexpr u32 PHI = phi(a);
template<u32 a> constexpr bool PRIME = PHI<a> +1 == a;

template<u32 M>
struct mint
{
	static_assert(0 < M);
	static_assert(M < 1u << 31);

	constexpr static u32 MOD = M;
	constexpr static u32 PHI = PHI<M>;
	constexpr static bool PRIME = PRIME<M>;
	constexpr static mint<PHI> INV_POW = M - 2;

	u32 v;

	constexpr mint() = default;
	template<class T, typename enable_if<is_integral<T>::value, int>::type = 0>
	constexpr mint(T v): v(v < 0 ? v % M + M : v % M) {}

	constexpr u32 val() const { return v; }
	constexpr friend mint operator+(mint a) { return a; }
	constexpr friend mint operator-(mint a) { if (a.v) a.v = M - a.v; return a; }
	constexpr mint& operator+=(mint b) { if ((v += b.v) >= M) v -= M; return *this; }
	constexpr friend mint operator+(mint a, mint b) { return a += b; }
	constexpr mint& operator-=(mint b) { if ((v += M - b.v) >= M) v -= M; return *this; }
	constexpr friend mint operator-(mint a, mint b) { return a -= b; }
	constexpr mint& operator*=(mint b) { v = u32((u64)v * b.v % M); return *this; }
	constexpr friend mint operator*(mint a, mint b) { return a *= b; }
	constexpr friend mint mpow(mint a, mint<PHI> b)
	{
		mint p = 1;
		for (; b.v; b.v /= 2, a *= a) if (b.v % 2) p *= a;
		return p;
	}
	constexpr mint inv() const
	{
		static_assert(PRIME);
		assert(v);
		return mpow(*this, INV_POW);
	}
	constexpr friend mint inv(mint a) { return a.inv(); }
	constexpr mint& operator/=(mint b) { return *this *= b.inv(); }
	constexpr friend mint operator/(mint a, mint b) { return a /= b; }
	constexpr friend bool operator==(mint a, mint b) { return a.v == b.v; }
	constexpr friend bool operator!=(mint a, mint b) { return a.v != b.v; }
	constexpr friend bool operator<(mint a, mint b) { return a.v < b.v; }
	constexpr friend bool operator<=(mint a, mint b) { return a.v <= b.v; }
	constexpr friend bool operator>(mint a, mint b) { return a.v > b.v; }
	constexpr friend bool operator>=(mint a, mint b) { return a.v >= b.v; }
	constexpr operator u32() const { return v; }
	friend istream& operator>>(istream& istrm, mint& a) { intmax_t v; istrm >> v; a = v; return istrm; }
	friend ostream& operator<<(ostream& ostrm, mint a) { return ostrm << a.v; }
};

template<u32... Ms> struct mints;
template<u32... Ms> constexpr mints<Ms...> mints_raw(u32 val);

template<>
struct mints<>
{
	constexpr static size_t SIZE = 0;
	constexpr static size_t size() { return SIZE; }
	constexpr static array<u32, SIZE> MODS{};
	constexpr static array<u32, SIZE> mods() { return MODS; }
	constexpr static bool PRIME = true;

	constexpr mints() = default;
	template<class T, typename enable_if<is_integral<T>::value, int>::type = 0>
	constexpr mints(T) {}
	constexpr void set_vals(u32*) const {}
	constexpr array<u32, SIZE> vals() const { return {}; }
	constexpr friend mints operator-(const mints&) { return {}; }
	constexpr friend mints operator+(const mints&, const mints&) { return {}; }
	constexpr mints& operator+=(const mints&) { return *this; }
	constexpr friend mints operator-(const mints&, const mints&) { return {}; }
	constexpr mints& operator-=(const mints&) { return *this; }
	constexpr friend mints operator*(const mints&, const mints&) { return {}; }
	constexpr mints& operator*=(const mints&) { return *this; }
};

template<u32 M, u32... Ms>
struct mints<M, Ms...>
{
	constexpr static size_t SIZE = mints<Ms...>::SIZE + 1;
	constexpr static size_t size() { return SIZE; }
	constexpr static array<u32, SIZE> MODS{ M, Ms... };
	constexpr static bool PRIME = mints<M>::PRIME && mints<Ms...>::PRIME;

	mint<M> h;
	mints<Ms...> t;

	constexpr mints() = default;
	template<class T, typename enable_if<is_integral<T>::value, int>::type = 0>
	constexpr mints(T v): h(v), t(v) {}
	constexpr mints(mint<M> h, const mints<Ms...>& t) : h(h), t(t) {}
	template<size_t S, size_t I>
	constexpr void set_vals(array<u32, S>& arr) const
	{
		static_assert(S < I);
		arr[I] = h.v;
		t.set_vals<S, I + 1>(arr);
	}
	constexpr array<u32, SIZE> vals() const
	{
		array<u32, SIZE> arr;
		set_vals(&arr[0]);
		return arr;
	}
	constexpr friend mints operator-(const mints& a)
	{
		return { -a.h, -a.t };
	}
	constexpr friend mints operator+(const mints& a, const mints& b)
	{
		return { a.h + b.h, a.t + b.t };
	}
	constexpr mints& operator+=(const mints& b)
	{
		h += b.h;
		t += b.t;
		return *this;
	}
	constexpr friend mints operator-(const mints& a, const mints& b)
	{
		return { a.h - b.h, a.t - b.t };
	}
	constexpr mints& operator-=(const mints& b)
	{
		h -= b.h;
		t -= b.t;
		return *this;
	}
	constexpr friend mints operator*(const mints& a, const mints& b)
	{
		return { a.h * b.h, a.t * b.t };
	}
	constexpr mints& operator*=(const mints& b)
	{
		h *= b.h;
		t *= b.t;
		return *this;
	}
};