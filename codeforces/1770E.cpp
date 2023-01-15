#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#ifndef DEBUG
#define assert(x) do {} while (false)
#endif // DEBUG

using namespace std;
using namespace chrono;
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

template<class T>
inline T read(istream& strm = cin)
{
	T x;
	strm >> x;
	return x;
}

template<class T>
constexpr T rup2(T x)
{
	static_assert(std::is_integral_v<T>);
	if (x == 0)
		return 1;
	x--;
	for (int i = 1; i < int(CHAR_BIT * sizeof(T)); i *= 2)
		x |= x >> i;
	return x + 1;
}

template<class T>
using os_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MK_TYPES(TYPE, NAME)using NAME=TYPE;using p##NAME=pair<NAME, NAME>;using a2##NAME=array<NAME, 2>;using v##NAME=vector<NAME>;using v##p##NAME=vector<p##NAME>;using v##a2##NAME=vector<a2##NAME>;using vv##NAME=vector<v##NAME>;using vv##p##NAME=vector<v##p##NAME>;using vv##a2##NAME=vector<v##a2##NAME>;using vvv##NAME=vector<vv##NAME>;using vvv##p##NAME=vector<vv##p##NAME>;using vvv##a2##NAME=vector<vv##a2##NAME>;using vvvv##NAME=vector<vvv##NAME>;using vvvv##p##NAME=vector<vvv##p##NAME>;using vvvv##a2##NAME=vector<vvv##a2##NAME>;using l##NAME=list<NAME>;using l##p##NAME=list<p##NAME>;using l##a2##NAME=list<a2##NAME>;using vl##NAME=vector<l##NAME>;using vl##p##NAME=vector<l##p##NAME>;using vl##a2##NAME=vector<l##a2##NAME>;using s##NAME=set<NAME>;using s##p##NAME=set<p##NAME>;using s##a2##NAME=set<a2##NAME>;using vs##NAME=vector<s##NAME>;using vs##p##NAME=vector<s##p##NAME>;using vs##a2##NAME=vector<s##a2##NAME>;template<class Pr> using S##NAME=set<NAME, Pr>;template<class Pr> using S##p##NAME=set<p##NAME, Pr>;template<class Pr> using S##a2##NAME=set<a2##NAME, Pr>;template<class Pr> using vS##NAME=vector<S##NAME<Pr>>;template<class Pr> using vS##p##NAME=vector<S##p##NAME<Pr>>;template<class Pr> using vS##a2##NAME=vector<S##a2##NAME<Pr>>;using ms##NAME=multiset<NAME>;using ms##p##NAME=multiset<p##NAME>;using ms##a2##NAME=multiset<a2##NAME>;using vms##NAME=vector<ms##NAME>;using vms##p##NAME=vector<ms##p##NAME>;using vms##a2##NAME=vector<ms##a2##NAME>;template<class Pr> using MS##NAME=multiset<NAME, Pr>;template<class Pr> using MS##p##NAME=multiset<p##NAME, Pr>;template<class Pr> using MS##a2##NAME=multiset<a2##NAME, Pr>;template<class Pr> using vMS##NAME=vector<MS##NAME<Pr>>;template<class Pr> using vMS##p##NAME=vector<MS##p##NAME<Pr>>;template<class Pr> using vMS##a2##NAME=vector<MS##a2##NAME<Pr>>;using us##NAME=unordered_set<NAME>;using us##p##NAME=unordered_set<p##NAME>;using us##a2##NAME=unordered_set<a2##NAME>;using vus##NAME=vector<us##NAME>;using vus##p##NAME=vector<us##p##NAME>;using vus##a2##NAME=vector<us##a2##NAME>;template<class H, class Eq> using US##NAME=unordered_set<NAME, H, Eq>;template<class H, class Eq> using US##p##NAME=unordered_set<p##NAME, H, Eq>;template<class H, class Eq> using US##a2##NAME=unordered_set<a2##NAME, H, Eq>;template<class H, class Eq> using vUS##NAME=vector<US##NAME<H, Eq>>;template<class H, class Eq> using vUS##p##NAME=vector<US##p##NAME<H, Eq>>;template<class H, class Eq> using vUS##a2##NAME=vector<US##a2##NAME<H, Eq>>;using ums##NAME=unordered_multiset<NAME>;using ums##p##NAME=unordered_multiset<p##NAME>;using ums##a2##NAME=unordered_multiset<a2##NAME>;using vums##NAME=vector<ums##NAME>;using vums##p##NAME=vector<ums##p##NAME>;using vums##a2##NAME=vector<ums##a2##NAME>;template<class H, class Eq> using UMS##NAME=unordered_multiset<NAME, H, Eq>;template<class H, class Eq> using UMS##p##NAME=unordered_multiset<p##NAME, H, Eq>;template<class H, class Eq> using UMS##a2##NAME=unordered_multiset<a2##NAME, H, Eq>;template<class H, class Eq> using vUMS##NAME=vector<UMS##NAME<H, Eq>>;template<class H, class Eq> using vUMS##p##NAME=vector<UMS##p##NAME<H, Eq>>;template<class H, class Eq> using vUMS##a2##NAME=vector<UMS##a2##NAME<H, Eq>>;using q##NAME=queue<NAME>;using q##p##NAME=queue<p##NAME>;using q##a2##NAME=queue<a2##NAME>;using vq##NAME=vector<q##NAME>;using vq##p##NAME=vector<q##p##NAME>;using vq##a2##NAME=vector<q##a2##NAME>;using d##NAME=deque<NAME>;using d##p##NAME=deque<p##NAME>;using d##a2##NAME=deque<a2##NAME>;using vd##NAME=vector<d##NAME>;using vd##p##NAME=vector<d##p##NAME>;using vd##a2##NAME=vector<d##a2##NAME>;using pq##NAME=priority_queue<NAME>;using pq##p##NAME=priority_queue<p##NAME>;using pq##a2##NAME=priority_queue<a2##NAME>;using vpq##NAME=vector<pq##NAME>;using vpq##p##NAME=vector<pq##p##NAME>;using vpq##a2##NAME=vector<pq##a2##NAME>;template<class Pr> using PQ##NAME=priority_queue<NAME, v##NAME, Pr>;template<class Pr> using PQ##p##NAME=priority_queue<p##NAME, v##p##NAME, Pr>;template<class Pr> using PQ##a2##NAME=priority_queue<a2##NAME, v##a2##NAME, Pr>;template<class Pr> using vPQ##NAME=vector<PQ##NAME<Pr>>;template<class Pr> using vPQ##p##NAME=vector<PQ##p##NAME<Pr>>;template<class Pr> using vPQ##a2##NAME=vector<PQ##a2##NAME<Pr>>;
MK_TYPES(bool, bl);
MK_TYPES(char, c8);
MK_TYPES(unsigned char, uc8);
MK_TYPES(int8_t, i8);
MK_TYPES(int16_t, i16);
MK_TYPES(int32_t, i32);
MK_TYPES(int64_t, i64)
MK_TYPES(__int128, i128);
MK_TYPES(uint8_t, u8);
MK_TYPES(uint16_t, u16);
MK_TYPES(uint32_t, u32);
MK_TYPES(uint64_t, u64);
MK_TYPES(unsigned __int128, u128);
MK_TYPES(float, f32);
MK_TYPES(double, f64);
MK_TYPES(long double, fld);
MK_TYPES(__float128, f128);
MK_TYPES(string, str8);

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
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int)(x).size()
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


constexpr bool is_prime(u32 M)
{
	if (M < 2)
		return false;
	for (u32 i = 2; (u64)i * i <= M; i++)
		if (M % i == 0)
			return false;
	return true;
}

template<u32 M> struct mint;
template<u32 M> constexpr mint<M> mint_raw(u32 val);

template<u32 M>
struct mint
{
	static_assert(M > 0);
	static_assert(M < 1u << 31);
	constexpr static u32 MOD = M;
	constexpr static u32 mod() { return MOD; }
	constexpr static bool PRIME = is_prime(M);

	u32 v;
	constexpr mint() = default;
	template<class T, typename enable_if<is_integral<T>::value, int>::type = 0>
	constexpr mint(T v):
		v(v < 0 ? v % M + M : v % M)
	{}
	constexpr u32 val() const
	{
		return v;
	}
	constexpr friend mint operator-(mint a)
	{
		return mint_raw<M>(a.v ? M - a.v : 0);
	}
	constexpr friend mint operator+(mint a, mint b)
	{
		u32 v = a.v + b.v;
		return mint_raw<M>(v >= M ? v - M : v);
	}
	constexpr mint& operator+=(mint b)
	{
		v = (*this + b).v;
		return *this;
	}
	constexpr friend mint operator-(mint a, mint b)
	{
		u32 v = a.v + M - b.v;
		return mint_raw<M>(v >= M ? v - M : v);
	}
	constexpr mint& operator-=(mint b)
	{
		v = (*this - b).v;
		return *this;
	}
	constexpr friend mint operator*(mint a, mint b)
	{
		return mint((u64)a.v * b.v);
	}
	constexpr mint& operator*=(mint b)
	{
		v = (*this * b).v;
		return *this;
	}
	template<class T, typename enable_if<is_integral<T>::value, int>::type = 0>
	constexpr friend mint pow(mint a, T b)
	{
		mint p = 1;
		while (b)
		{
			if (b % 2)
				p *= a;
			b /= 2;
			a *= a;
		}
		return p;
	}
	constexpr mint inv() const
	{
		static_assert(PRIME);
		assert(*this);
		return pow(*this, M - 2);
	}
	constexpr friend mint inv(mint a)
	{
		static_assert(PRIME);
		assert(a);
		return a.inv();
	}
	constexpr friend mint operator/(mint a, mint b)
	{
		static_assert(PRIME);
		assert(b);
		return a * b.inv();
	}
	constexpr mint& operator/=(mint b)
	{
		static_assert(PRIME);
		assert(b);
		v = (*this / b).v;
		return *this;
	}
	constexpr friend bool operator==(mint a, mint b)
	{
		return a.v == b.v;
	}
	constexpr friend bool operator!=(mint a, mint b)
	{
		return a.v != b.v;
	}
	constexpr friend bool operator<(mint a, mint b)
	{
		return a.v < b.v;
	}
	constexpr friend bool operator<=(mint a, mint b)
	{
		return a.v <= b.v;
	}
	constexpr friend bool operator>(mint a, mint b)
	{
		return a.v > b.v;
	}
	constexpr friend bool operator>=(mint a, mint b)
	{
		return a.v >= b.v;
	}
	constexpr operator u32() const
	{
		return v;
	}
	friend istream& operator>>(istream& istrm, mint& a)
	{
		intmax_t v;
		istrm >> v;
		a = v;
		return istrm;
	}
	friend ostream& operator<<(ostream& ostrm, mint a)
	{
		return ostrm << a.v;
	}
};
template<u32 M>
constexpr mint<M> mint_raw(u32 v)
{
	assert(v < M);
	mint<M> m;
	m.v = v;
	return m;
}

// Settings Macros:
//#define T_CASES
//#define PRECOMP
//#define PT_NUMS

#ifdef PRECOMP
void pre();
#endif // PRECOMP
void go();

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

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

constexpr u32 MOD = 998244353;
typedef mint<MOD> mnt;
constexpr auto I2 = mnt(2).inv();

struct res
{
	mnt a, b, s;
};

res dfs(const vvi32& G, const vector<mnt>& P, int u, int v)
{
	mnt A = 0, B = 0, S = 0;
	for (int w : G[v])
	{
		if (w == u)
			continue;
		auto [a, b, s] = dfs(G, P, v, w);
		a += P[w];
		b += a;
		A += a;
		B += b;
		S += s;
	}
	S += P[v] * B;
	return { A, B, S };
}

void go()
{
	int n, k;
	cin >> n >> k;
	vi32 A(k);
	for (int& a : A)
	{
		cin >> a;
		a--;
	}
	vpi32 E(n - 1);
	for (auto& [u, v] : E)
	{
		cin >> u >> v;
		u--;
		v--;
	}
	vector<mnt> P(n);
	for (int a : A)
		P[a] = 1;
	for (mnt p : P) cerr << p << ' ';
	cerr << endl;
	for (auto [u, v] : E)
		P[u] = P[v] = I2 * (P[u] + P[v]);

	cerr << I2 << endl;

	for (mnt p : P) cerr << p << ' ';
	cerr << endl;

	vvi32 G(n);
	for (auto [u, v] : E)
	{
		//cerr << u << ' ' << v << endl;
		G[u].push_back(v);
		G[v].push_back(u);
	}


	auto [a, b, s] = dfs(G, P, -1, 0);
	s *= 2;
	s /= (u64)k * (k - 1);
	cout << s;
}
