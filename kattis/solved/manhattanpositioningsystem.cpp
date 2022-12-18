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

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

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

enum class tp
{
	MT,
	PT,
	PSEG,
	NSEG,
};

// MT: nothing
// PT: (x,y)=(a,b)
// PSEG: y=c+x for a<=x<=b
// NSEG: y=c-x for a<=x<=b

constexpr int NIL = MIN<int>;

struct pset
{
	tp t;
	int a, b, c;
	bool in(int x) const
	{
		switch (t)
		{
		case tp::MT: return false;
		case tp::PT: return x == a;
		case tp::PSEG:
		case tp::NSEG:
		default: return a <= x && x <= b;
		}
	}
	int operator()(int x) const
	{
		if (!in(x)) return NIL;
		switch (t)
		{
		case tp::PT: return b;
		case tp::PSEG: return c + x;
		case tp::NSEG:
		default: return c - x;
		}
	}
	constexpr explicit pset(tp t = tp::MT, int a = 0, int b = 0, int c = 0):
		t(t),
		a(a),
		b(b),
		c(c)
	{
		if (t == tp::PSEG || t == tp::NSEG)
		{
			if (a > b)
				this->t = tp::MT;
			else if (a == b)
			{
				this->b = (*this)(a);
				this->t = tp::PT;
			}
		}
	}
};
constexpr pset MT(tp::MT);

vector<pset> beacon(int x, int y, int d)
{
	if (d == 0) return { pset(tp::PT, x, y) };
	else if (d == 1) return {
		pset(tp::PT, x - 1, y),
		pset(tp::PT, x, y + 1),
		pset(tp::PT, x, y - 1),
		pset(tp::PT, x + 1, y),
	};
	else return {
		// (x - d, y) -> (x - 1, y + d - 1)
		pset(tp::PSEG, x - d, x - 1, y - x + d),
		// (x - d + 1, y - 1) -> (x, y - d)
		pset(tp::NSEG, x - d + 1, x, y + x - d),
		// (x, y + d) -> (x + d - 1, y + 1)
		pset(tp::NSEG, x, x + d - 1, y + x + d),
		// (x + 1, y - d + 1) -> (x + d, y)
		pset(tp::PSEG, x + 1, x + d, y - x - d),
	};
}

pset isect(pset a, pset b)
{
	if (a.t == tp::MT || b.t == tp::MT)
		exit(-1);
	switch (a.t)
	{
	case tp::MT: return MT;
	case tp::PT: return b(a.a) == a.b ? a : MT;
	case tp::PSEG:
		switch (b.t)
		{
		case tp::MT: return MT;
		case tp::PT: return isect(b, a);
		case tp::PSEG: return a.c == b.c ? pset(tp::PSEG, max(a.a, b.a), min(a.b, b.b), a.c) : MT;
		case tp::NSEG:
		default: {
			int x2 = b.c - a.c;
			int x = x2 / 2;
			return x2 % 2 == 0 && a.in(x) && b.in(x) ? pset(tp::PT, x, a(x)) : MT;
		}
		}
	case tp::NSEG:
	default:
		switch (b.t)
		{
		case tp::MT: return MT;
		case tp::PT:
		case tp::PSEG: return isect(b, a);
		case tp::NSEG:
		default: return a.c == b.c ? pset(tp::NSEG, max(a.a, b.a), min(a.b, b.b), a.c) : MT;
		}
	}
}

void isect(const vector<pset>& A, const vector<pset>& B, vector<pset>& C)
{
	C.clear();
	for (pset a : A)
		for (pset b : B)
		{
			pset c = isect(a, b);
			if (c.t == tp::MT) continue;
			C.push_back(c);
		}
}


void dbg(const vector<pset>& S)
{
#ifdef DEBUG
	cerr << '{';
	for (pset s : S)
	{
		switch (s.t)
		{
		case tp::MT: cerr << "MT"; break;
		case tp::PT: cerr << "PT(" << s.a << ',' << s.b << ')'; break;
		case tp::PSEG: cerr << "PSEG(" << s.a << ',' << s(s.a) << ")-(" << s.b << ',' << s(s.b) << ')'; break;
		case tp::NSEG: cerr << "NSEG(" << s.a << ',' << s(s.a) << ")-(" << s.b << ',' << s(s.b) << ')'; break;
		}
		cerr << ',';
	}
	cerr << '}' << endl;
	if (sz(S) == 4)
		cerr << S[2](1000200) << endl;
#endif
}

void go()
{
	int n;
	cin >> n;
	int x, y, d;
	cin >> x >> y >> d;
	vector<pset> S = beacon(x, y, d), S2;
	//dbg(S);
	rep(i, 1, n)
	{
		cin >> x >> y >> d;
		swap(S, S2);
		isect(S2, beacon(x, y, d), S);
		//dbg(S);
	}
	if (S.empty())
	{
		cout << "impossible";
	}
	else if (S.size() > 1 || S[0].t != tp::PT)
	{
		cout << "uncertain";
	}
	else
	{
		cout << S[0].a << ' ' << S[0].b;
	}
}