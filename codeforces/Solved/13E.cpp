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
/*
struct Node { // Splay tree. Root's pp contains tree's parent.
	Node *p = 0, *pp = 0, *c[2];
	int i, n;
	bool flip = 0;
	Node() { c[0] = c[1] = 0; fix(); }
	void fix() {
		n = 1;
		if (c[0]) c[0]->p = this;
		if (c[1]) c[1]->p = this;
		if (c[0]) n += c[0]->n;
		if (c[1]) n += c[1]->n;
		// (+ update sum of subtree elements etc. if wanted)
	}
	void pushFlip() {
		if (!flip) return;
		flip = 0; swap(c[0], c[1]);
		if (c[0]) c[0]->flip ^= 1;
		if (c[1]) c[1]->flip ^= 1;
	}
	int up() { return p ? p->c[1] == this : -1; }
	void rot(int i, int b) {
		int h = i ^ b;
		Node *x = c[i], *y = b == 2 ? x : x->c[h], *z = b ? y : x;
		if ((y->p = p)) p->c[up()] = y;
		c[i] = z->c[i ^ 1];
		if (b < 2) {
			x->c[h] = y->c[h ^ 1];
			z->c[h ^ 1] = b ? x : this;
		}
		y->c[i ^ 1] = b ? this : x;
		fix(); x->fix(); y->fix();
		if (p) p->fix();
		swap(pp, y->pp);
	}
	void splay() { /// Splay this up to the root. Always finishes without flip set.
		for (pushFlip(); p; ) {
			if (p->p) p->p->pushFlip();
			p->pushFlip(); pushFlip();
			int c1 = up(), c2 = p->up();
			if (c2 == -1) p->rot(c1, 2);
			else p->p->rot(c2, c1 != c2);
		}
	}
	Node* first() { /// Return the min element of the subtree rooted at this, splayed to the top.
		pushFlip();
		return c[0] ? c[0]->first() : (splay(), this);
	}
};

struct LinkCut {
	vector<Node> node;
	LinkCut(int N) : node(N) {}

	void link(int u, int v) { // add an edge (u, v)
		assert(!connected(u, v));
		makeRoot(&node[u]);
		node[u].pp = &node[v];
	}
	void cut(int u, int v) { // remove an edge (u, v)
		Node *x = &node[u], *top = &node[v];
		makeRoot(top); x->splay();
		assert(top == (x->pp ?: x->c[0]));
		if (x->pp) x->pp = 0;
		else {
			x->c[0] = top->p = 0;
			x->fix();
		}
	}
	bool connected(int u, int v) { // are u, v in the same tree?
		Node* nu = access(&node[u])->first();
		return nu == access(&node[v])->first();
	}
	void makeRoot(Node* u) { /// Move u to root of represented tree.
		access(u);
		u->splay();
		if(u->c[0]) {
			u->c[0]->p = 0;
			u->c[0]->flip ^= 1;
			u->c[0]->pp = u;
			u->c[0] = 0;
			u->fix();
		}
	}
	Node* access(Node* u) { /// Move u to root aux tree. Return the root of the root aux tree.
		u->splay();
		while (Node* pp = u->pp) {
			pp->splay(); u->pp = 0;
			if (pp->c[1]) {
				pp->c[1]->p = 0; pp->c[1]->pp = pp; }
			pp->c[1] = u; pp->fix(); u = pp;
		}
		return u;
	}
};*/


struct Node {
	Node* p = 0, * pp = 0, * c[2]{};
	int n = 1, i;
	bool flip = 0;
	Node() { fix(); }
	void fix() {
		n = 1;
		rep(i, 0, 2)
			if (c[i]) {
				c[i]->p = this;
				n += c[i]->n;
			}
	}
	void pushFlip() {
		if (!flip) return;
		flip = 0; swap(c[0], c[1]);
		rep(i, 0, 2) if (c[i]) c[i]->flip ^= 1;
	}
	int up() { return p ? p->c[1] == this : -1; }
	void rot(int i, int b) {
		int h = i ^ b;
		Node* x = c[i], * y = b == 2 ? x : x->c[h], * z = b ? y : x;
		if ((y->p = p)) p->c[up()] = y;
		c[i] = z->c[i ^ 1];
		if (b < 2) {
			x->c[h] = y->c[h ^ 1];
			z->c[h ^ 1] = b ? x : this;
		}
		y->c[i ^ 1] = b ? this : x;
		fix(); x->fix(); y->fix();
		if (y->p) y->p->fix();
		swap(pp, y->pp);
	}
	void splay() {
		for (pushFlip(); p;) {
			if (p->p) p->p->pushFlip();
			p->pushFlip(); pushFlip();
			int c1 = up(), c2 = p->up();
			if (c2 == -1) p->rot(c1, 2);
			else p->p->rot(c2, c1 != c2);
		}
	}
	Node* first() {
		pushFlip();
		return c[0] ? c[0]->first() : (splay(), this);
	}
};

struct LinkCut {
	vector<Node> node;
	LinkCut(int N) : node(N) {}
	void link(int u, int v) {
		assert(!connected(u, v));
		makeRoot(&node[u]);
		node[u].pp = &node[v];
	}
	void cut(int u, int v) {
		Node* x = &node[u], * top = &node[v];
		makeRoot(top);
		x->splay();
		assert(top == (x->pp ? : x->c[0]));
		if (x->pp) x->pp = 0;
		else {
			x->c[0] = top->p = 0;
			x->fix();
		}
	}
	bool connected(int u, int v) {
		Node* nu = access(&node[u])->first();
		return nu == access(&node[v])->first();
	}
	void makeRoot(Node* u) {
		access(u);
		if (u->c[0]) {
			u->c[0]->p = 0;
			u->c[0]->flip ^= 1;
			u->c[0]->pp = u;
			u->c[0] = 0;
			u->fix();
		}
	}
	Node* access(Node* u) {
		Node* v = u;
		u->splay();
		if (u->c[1]) {
			u->c[1]->p = 0; u->c[1]->pp = u;
		}
		u->c[1] = 0;
		u->fix();
		while (Node* pp = u->pp) {
			pp->splay(); u->pp = 0;
			if (pp->c[1]) {
				pp->c[1]->p = 0; pp->c[1]->pp = pp;
			}
			pp->c[1] = u;
			pp->fix();
			u = pp;
		}
		v->splay();
		return v;
	}
};

void go() {
	int n, m;
	cin >> n >> m;
	vi A(n);
	for (int i = 0; i < n; i++) {
		cin >> A[i];
		A[i] += i;
	}
	LinkCut LC(n);
	for (int i = 0; i < n; i++)
		LC.node[i].i = i;
	for (int i = 0; i < n; i++) {
		if (A[i] < n)
			LC.link(i, A[i]);
	}

	while (m--) {
		int t, i, a;
		cin >> t;
		if (t == 0) {
			cin >> i >> a;
			i--;
			if (A[i] < n) {
				Node* r = LC.access(&LC.node[i])->first();
				LC.cut(i, A[i]);
				LC.makeRoot(r);
			}
			A[i] = i + a;
			if (A[i] < n) {
				LC.link(i, A[i]);
			}
		}
		else {
			cin >> i;
			i--;
			Node* u = LC.access(&LC.node[i]);
			int n = u->n;
			Node* r = u->first();
			cout << r->i + 1 << ' ' << n << endl;
		}
	}
}