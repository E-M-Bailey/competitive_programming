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
struct TupleHashHelper {
	typedef std::tuple<Ts...> Tup;
	typedef TupleHashHelper<S - 1, Ts...> Helper;
	typedef std::tuple_element_t<S - 1, Tup> T;
	inline constexpr size_t operator()(const Tup& t) const noexcept {
		return (size_t)31 * Helper()(t) + std::hash<T>()(std::get<S - 1>(t));
	}
};

template<class... Ts>
struct TupleHashHelper<0, Ts...> {
	typedef std::tuple<Ts...> Tup;
	inline constexpr size_t operator()(const Tup&) const noexcept {
		return 0;
	}
};

template<class... Ts>
struct std::hash<tuple<Ts...>> {
	typedef std::tuple<Ts...> Tup;
	static constexpr size_t S = sizeof...(Ts);
	typedef TupleHashHelper<S, Ts...> Helper;
	inline constexpr size_t operator()(const Tup& t) const noexcept {
		return Helper()(t);
	}
};

template<class T, class U>
struct std::hash<pair<T, U>> {
	inline constexpr size_t operator()(const pair<T, U>& p) const noexcept {
		return (size_t)31 * hash<T>()(p.first) + hash<U>()(p.second);
	}
};

template<class T>
inline T read(istream& strm = cin) {
	T x;
	strm >> x;
	return x;
}

template<class T>
constexpr T rup2(T x) {
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
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
typedef long long ll;
typedef pi32 pii;
typedef a2i32 aii;
typedef vi32 vi;
typedef vvi32 vvi;
typedef vi64 vll;
typedef vbl vb;
mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());

#ifndef LP_TREAP_H_INCLUDED
#define LP_TREAP_H_INCLUDED

#ifndef TEMPLATE_H_INCLUDED
#include "template.h"
#endif // TEMPLATE_H_INCLUDED

// Lazy-prop, optionally persistent implicit treap forest
// p l k i a: only for pers, lazy, key, index, accum ops resp.
int rnd() {
	static uniform_int_distribution<int> d(INT_MIN, INT_MAX - 1);
	return d(randy);
}
struct B { unsigned r : 31, d : 1; };
struct LPTreap {
	typedef int V;
	typedef int64_t S; static constexpr S SID = 0; //a
	typedef bool L; static constexpr L LID = 0; //l
	// prior time(p) size(i) children val sum(a) lazy(l) key(k)
	struct N { int p, n; aii c; V v; S s; L l; };
	// nodes stack time(p)
	vector<N> T; vector<B> R;
	int p(int i) { return i < 0 ? INT_MAX : T[i].p; }
	S s(int i) { return i < 0 ? SID : T[i].s; } //a
	int n(int i) { return i < 0 ? 0 : T[i].n; } //i
	void f(N& n) { n.s = n.v + s(n.c[0]) + s(n.c[1]); } //a
	void g(N& n) { swap(n.c[0], n.c[1]); } //l
	void h(N& p, N& c) { c.l ^= 1; } //l
	bool l(N& n) { return n.l != LID; } //l
	void upd(int r) { //a|i if neither a nor i, delete upd's body
		if (r >= 0) {
			f(T[r]); //a
			T[r].n = 1 + n(T[r].c[0]) + n(T[r].c[1]); //i
		}
	}
	int mk(N n) {
		int r = sz(T); T.push_back(n); f(T[r]); return r;
	}
	int mk(V v) { // change based on deleted fields
		return mk({ rnd(), 1, { -1, -1 }, v, SID, LID });
	}
	//c: if persistence unneeded, just return r
	int c(int& r) { return r; } //p
	int pd(int& r) { //l: if not lazy, just return c(r)
		if (c(r) >= 0 && l(T[r])) {
			rep(d, 0, 2) if (c(T[r].c[d]) >= 0)
				h(T[r], T[T[r].c[d]]); g(T[r]); T[r].l = LID;
		} return r;
	}
	B pop() { B b = R.back(); R.pop_back(); return b; }
	void push(int r, bool d) { R.push_back({ r, d }); }
	template<bool Pd/*x goes right*/> void ri(int r, int x) { //i
		while (pd(r) >= 0) {
			int y = n(T[r].c[0]); bool d = Pd ? y < x : y <= x;
			push(r, d);	r = T[r].c[d]; if (d) x -= y + 1;
		}
	}
	void rj(aii a) {
		while (max(a[0], a[1]) >= 0) {
			bool d = p(a[0]) > p(a[1]); push(pd(a[d]), d);
			a[d] = T[a[d]].c[!d];
		}
	}
	pii spt() { // split
		aii a{ -1, -1 }; while (sz(R)) {
			auto [r, d] = pop(); T[r].c[d] = a[!d]; upd(a[!d] = r);
		} return { a[0], a[1] };
	}
	template<bool d/*x goes right*/>
	pii spti(int r, int x) { ri<d>(r, x); return spt(); } //i
	int jn(int r, int s) { // join
		rj({ r, s }); r = -1; while (sz(R)) {
			auto [a, d] = pop(); T[a].c[!d] = r; upd(r = a);
		} return r;
	}
	template<bool d/*right*/> int xtr(int r) { // extremum
		if (r >= 0) while (T[r].c[d] >= 0) r = T[r].c[d]; return r;
	}
	template<bool d/*right*/> int bnd() { // bound
		int s = -1; while (sz(R)) {
			auto [r, e] = pop(); s = r; if (e ^ d) break;
		} R.clear(); return s;
	}
	template<bool d/*right*/, bool Pd/*x goes right*/>
	int bndi(int r, int x) { ri<Pd>(r, x); return bnd<d>(); } //i
	int geti(int r, int x) { //i
		return 0 <= x && x < T[r].n ? bndi<1, 1>(r, x) : -1;
	}
	int tree(const vi& A) { // A: sorted non-lazy isolated nodes
		int r, p; for (int a : A) {
			c(a); r = -1; while (sz(R) && T[a].p < T[R.back().r].p)
				upd(r = pop().r);
			T[a].c[0] = r; p = sz(R) ? R.back().r : -1; upd(a);
			push(a, 0); if (p >= 0) T[p].c[1] = a;
		} r = -1; while (sz(R)) upd(r = pop().r); return r;
	}
	template<bool Pd, class F> void io(int& r, const F& f) {
		if (r < 0) return; if (Pd) pd(r);
		io<Pd>(T[r].c[0], f); f(r); io<Pd>(T[r].c[1], f);
	} // Pd: pushdown all nodes
};

#endif

// Settings Macros:
//#define T_CASES
//#define PRECOMP
//#define PT_NUMS

#ifdef PRECOMP
void pre();
#endif // PRECOMP
void go();

int main(int argc, const char* argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef PRECOMP
	pre();
#endif // PRECOMP

#ifdef T_CASES
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++) {
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

void go() {
	int n, m;
	cin >> n >> m;
	LPTreap T;
	T.T.reserve(n);
	vi32 A(n);
	for (int& a : A) {
		int x;
		cin >> x;
		a = T.mk(x);
	}
	int r = T.tree(A), s, t;
	while (m--) {
		int q, a, b;
		cin >> q >> a >> b;
		tie(r, t) = T.spti<1>(r, b);
		tie(r, s) = T.spti<1>(r, a - 1);
		if (q == 1)
			T.T[s].l ^= 1;
		else
			cout << T.T[s].s << '\n';
		r = T.jn(r, s);
		r = T.jn(r, t);
	}
}
