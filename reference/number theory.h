#ifndef NUMBER_THEORY_H_INCLUDED
#define NUMBER_THEORY_H_INCLUDED

#ifndef TEMPLATE_H_INCLUDED
#include "template.h"
#endif // TEMPLATE_H_INCLUDED

template<class T>
constexpr T bin_gcd(T l, T r) {
	if (!(l && r))
		return l | r;
	int s = __builtin_ctz(l | r);
	l >>= __builtin_ctz(l);
	do {
		r >>= __builtin_ctz(r);
		if (l > r)
			swap(l, r);
		r -= l;
	} while (r);
	return l << s;
}

template<class T>
constexpr T gcd(const T& l, const T& r) {
	if constexpr (is_integral_v<T>)
		return bin_gcd(l, r);
	else {
		T a = abs(l), b = abs(r);
		while (b)
			tie(a, b) = make_pair(b, a % b);
		return a;
	}
}

template<class T>
constexpr T gcd(initializer_list<T> args) {
	return accumulate(args.begin(), args.end(), (T)0, gcd<T>);
}

template<class T>
constexpr T lcm(const T& l, const T& r) {
	return (l | r) ? l / gcd(l, r) * r : 0;
}

template<class T>
constexpr T lcm(initializer_list<T> args) {
	return accumulate(args.begin(), args.end(), (T)1, lcm<T>);
}

template<class T>
constexpr bool coprime(T l, T r) {
	return gcd(l, r) == 1;
}

template<class T>
struct bezout {
	T gcd, x, y;
};

template<class T>
constexpr bezout<T> eEuclid(const T& l, const T& r) {
	T a = abs(l), b = abs(r);
	vector<pair<T, T>> S;
	while (b != 0) {
		S.emplace_back(a, b);
		tie(a, b) = make_pair(b, a % b);
	}
	bezout<T> ans{a, 1, 0};
	for (; !S.empty(); S.pop_back()) {
		tie(a, b) = S.back();
		tie(ans.x, ans.y) = make_pair(ans.y, ans.x - a / b * ans.y);
	}
	return ans;
}

template<class T, class U>
constexpr T pos_mod(const T& n, const U& mod) {
	if (n >= 0)
		return n >= mod ? n % mod : n;
	else {
		T ans = n % mod;
		return ans == 0 ? ans : ans + mod;
	}
}

template<class T>
constexpr T mod_inv(const T& n, const T& mod) {
	bezout<T> bz = eEuclid(n, mod);
	assert(bz.gcd == 1);
	return pos_mod(bz.x, mod);
}

template<class T, uintmax_t M = 0>
struct mod_int {
	static constexpr T MOD = M;

	T value;

	constexpr T mod() const {
		return MOD;
	}

	constexpr mod_int() :
		value(0)
	{}

	template<class U>
	constexpr mod_int(const U& value) :
		value(static_cast<T>(pos_mod(value, MOD)))
	{}

	constexpr mod_int(mod_int&& x) noexcept :
		value(x.value)
	{}

	constexpr mod_int(const mod_int& x) :
		value(x.value)
	{}

	constexpr mod_int& operator=(const mod_int& x) {
		this->value = x.value;
		return *this;
	}

	inline mod_int& operator=(mod_int&& x) noexcept {
		this->value = x.value;
		return *this;
	}

	template<class U>
	constexpr mod_int& operator=(const U& value) {
		this->value = static_cast<T>(pos_mod(value, MOD));
		return value;
	}

	template<class U>
	inline mod_int& operator=(U&& value) noexcept {
		this->value = static_cast<T>(pos_mod(value, MOD));
		return *this;
	}

	explicit constexpr operator T&() noexcept {
		return value;
	}

	explicit constexpr operator const T&() const noexcept {
		return value;
	}

	explicit constexpr operator bool() const {
		return static_cast<bool>(value);
	}

	constexpr bool operator!() const {
		return !value;
	}

	template<class U>
	explicit constexpr operator U() const {
		return static_cast<U>(value);
	}
};

template<class T, uintmax_t M>
constexpr bool same_mod(const mod_int<T, M>& a, const mod_int<T, M>& b) {
	if (M > 0)
		return true;
	else
		return a.mod() == b.mod();
}

template<class T>
struct mod_int<T, 0> {
	const T MOD;
	T value;

	constexpr T mod() const {
		return MOD;
	}

	template<class U>
	explicit constexpr mod_int(const U& mod) :
		MOD(static_cast<T>(mod)),
		value(0)
	{}

	template<class U, class V>
	constexpr mod_int(const U& mod, const V& value) :
		MOD(static_cast<T>(mod)),
		value(static_cast<T>(pos_mod(value, mod))) {
		assert(mod > 0);
	}

	constexpr mod_int(mod_int&& x) noexcept :
		MOD(x.MOD),
		value(x.value)
	{}

	constexpr mod_int(const mod_int& x) :
		MOD(x.MOD),
		value(x.value)
	{}

	constexpr mod_int& operator=(const mod_int& x) {
		assert(same_mod(*this, x));
		this->value = x.value;
		return *this;
	}

	inline mod_int& operator=(mod_int&& x) noexcept {
		assert(same_mod(*this, x));
		this->value = x.value;
		return *this;
	}

	template<class U>
	constexpr mod_int& operator=(const U& value) {
		this->value = static_cast<T>(pos_mod(value, MOD));
		return value;
	}

	template<class U>
	inline mod_int& operator=(U&& value) noexcept {
		this->value = static_cast<T>(pos_mod(value, MOD));
		return *this;
	}

	explicit constexpr operator T&() noexcept {
		return value;
	}

	explicit constexpr operator const T&() const noexcept {
		return value;
	}

	explicit constexpr operator bool() const {
		return static_cast<bool>(value);
	}

	constexpr bool operator!() const {
		return !value;
	}

	template<class U>
	explicit constexpr operator U() const {
		return static_cast<U>(value);
	}
};

template<class T, uintmax_t M>
constexpr mod_int<T, M> mk_mod_int(const T& mod, const T& value) {
	if constexpr(M) {
		assert(M == mod);
		return mod_int<T, M>(value);
	} else
		return mod_int<T, M>(mod, value);
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> inv(mod_int<T, M> n) {
	n.value = mod_inv(n.value, n.mod());
	return n;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> operator+(mod_int<T, M> l) {
	return l;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> operator-(mod_int<T, M> l) {
	l.value = l.value ? l.mod() - l.value : 0;
	return l;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M>& operator+=(mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	l.value = l.value + r.value;
	if (l.value >= l.mod())
		l.value -= l.mod();
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M>& operator+=(mod_int<T, M>& l, const U& r) {
	return l += mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M>
constexpr mod_int<T, M>& operator++(mod_int<T, M>& l) {
	return l += 1;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> operator++(mod_int<T, M>& l, int) {
	mod_int old = l;
	++l;
	return old;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> operator+(mod_int<T, M> l, const mod_int<T, M>& r) {
	l += r;
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M> operator+(mod_int<T, M> l, const U& r) {
	return l + mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M> operator+(const U& l, const mod_int<T, M>& r) {
	return mk_mod_int<T, M>(r.mod(), l) + r;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M>& operator-=(mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	l.value = l.value - r.value;
	if (is_unsigned_v<T> ? l.value >= l.mod() : l.value < 0)
		l.value += l.mod();
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M>& operator-=(mod_int<T, M>& l, const U& r) {
	return l -= mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M>
constexpr mod_int<T, M>& operator--(mod_int<T, M>& l) {
	return l -= 1;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> operator--(mod_int<T, M>& l, int) {
	mod_int old = l;
	--l;
	return old;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> operator-(mod_int<T, M> l, const mod_int<T, M>& r) {
	l -= r;
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M> operator-(const mod_int<T, M>& l, const U& r) {
	return l - mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M> operator-(const U& l, const mod_int<T, M>& r) {
	return mk_mod_int<T, M>(r.mod(), l) - r;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M>& operator*=(mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	l.value = (l.value * r.value) % l.mod();
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M>& operator*=(mod_int<T, M>& l, const U& r) {
	return l *= mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> operator*(mod_int<T, M> l, const mod_int<T, M>& r) {
	l *= r;
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M> operator*(mod_int<T, M> l, const U& r) {
	l *= r;
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M> operator*(const U& l, mod_int<T, M> r) {
	r *= l;
	return r;
}

template<class T, uintmax_t M>
constexpr mod_int<T, M>& operator/=(mod_int<T, M>& l, const mod_int<T, M>& r) {
	return l *= inv(r);
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M>& operator/=(mod_int<T, M>& l, const U& r) {
	return l /= mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M>
constexpr mod_int<T, M> operator/(mod_int<T, M> l, const mod_int<T, M>& r) {
	l /= r;
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M> operator/(mod_int<T, M> l, const U r) {
	l /= r;
	return l;
}

template<class T, uintmax_t M, class U>
constexpr mod_int<T, M> operator/(const U& l, const mod_int<T, M>& r) {
	return l * inv(r);
}

template<class T, uintmax_t M>
constexpr bool operator==(const mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	return l.value == r.value;
}

template<class T, uintmax_t M, class U>
constexpr bool operator==(const mod_int<T, M>& l, const U& r) {
	return l == mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M, class U>
constexpr bool operator==(const U& l, const mod_int<T, M>& r) {
	return mk_mod_int<T, M>(r.mod(), l) == r;
}

template<class T, uintmax_t M>
constexpr bool operator!=(const mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	return l.value != r.value;
}

template<class T, uintmax_t M, class U>
constexpr bool operator!=(const mod_int<T, M>& l, const U& r) {
	return l != mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M, class U>
constexpr bool operator!=(const U& l, const mod_int<T, M>& r) {
	return mk_mod_int<T, M>(r.mod(), l) != r;
}

template<class T, uintmax_t M>
constexpr bool operator<(const mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	return l.value < r.value;
}

template<class T, uintmax_t M, class U>
constexpr bool operator<(const mod_int<T, M>& l, const U& r) {
	return l < mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M, class U>
constexpr bool operator<(const U& l, const mod_int<T, M>& r) {
	return mk_mod_int<T, M>(r.mod(), l) < r;
}

template<class T, uintmax_t M>
constexpr bool operator>(const mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	return l.value > r.value;
}

template<class T, uintmax_t M, class U>
constexpr bool operator>(const mod_int<T, M>& l, const U& r) {
	return l > mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M, class U>
constexpr bool operator>(const U& l, const mod_int<T, M>& r) {
	return mk_mod_int<T, M>(r.mod(), l) > r;
}

template<class T, uintmax_t M>
constexpr bool operator<=(const mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	return l.value <= r.value;
}

template<class T, uintmax_t M, class U>
constexpr bool operator<=(const mod_int<T, M>& l, const U& r) {
	return l <= mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M, class U>
constexpr bool operator<=(const U& l, const mod_int<T, M>& r) {
	return mk_mod_int<T, M>(r.mod(), l) < r;
}

template<class T, uintmax_t M>
constexpr bool operator>=(const mod_int<T, M>& l, const mod_int<T, M>& r) {
	assert(same_mod(l, r));
	return l.value >= r.value;
}

template<class T, uintmax_t M, class U>
constexpr bool operator>=(const mod_int<T, M>& l, const U& r) {
	return l >= mk_mod_int<T, M>(l.mod(), r);
}

template<class T, uintmax_t M, class U>
constexpr bool operator>=(const U& l, const mod_int<T, M>& r) {
	return mk_mod_int<T, M>(r.mod(), l) >= r;
}

template<class T, uintmax_t M>
inline istream& operator>>(istream& strm, mod_int<T, M>& n) {
	strm >> n.value;
	n.value = pos_mod(n.value, n.mod());
	return strm;
}

template<class T, uintmax_t M>
inline ostream& operator<<(ostream& strm, const mod_int<T, M>& n) {
	return strm << n.value;
}

//#define MOD 0ll
//#define MOD 1000000007ll
#define MOD 998244353ll
// #define MOD 998244853ll
#define MINT_DEF mod_int<i64, MOD>
MK_TYPES(MINT_DEF, mint);

// TODO multiple inverses

//template<class InputIt, class OutputIt>
//constexpr void mod_inv(InputIt first, InputIt last, OutputIt d_first, class iterator_traits<InputIt>::value_type mod)
//{
//	typedef class iterator_traits<InputIt>::value_type T;
//
//	size_t n = 0;
//}

#endif // NUMBER_THEORY_H_INCLUDED
