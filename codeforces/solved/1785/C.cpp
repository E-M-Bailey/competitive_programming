#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifdef DEBUG
#define DBG(x) x
#define dassert(x) assert(x)
#else
#define DBG(x)
#define dassert(x) do {} while (0)
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

template<class T> [[nodiscard]] constexpr enable_if_t<is_integral_v<T>, T> rup2(T x) noexcept
{
	if (x-- == 0) return 1;
	for (int i = 1; i < int(CHAR_BIT * sizeof(T)); i *= 2) x |= x >> i;
	return ++x;
}

template<class T, class C = char, class Tr = char_traits<C>> [[nodiscard]] T read(basic_istream<C, Tr>& is) { T x; is >> x; return x; }
template<class R, class C = char, class Tr = char_traits<C>> basic_istream<C, Tr>& range_read(basic_istream<C, Tr>& is, R& r) { for (auto& x : r) is >> x; return is; }
template<class... Ts, class C = char, class Tr = char_traits<C>> [[nodiscard]] constexpr auto variadic_reader(basic_istream<C, Tr>& is) { return [&is](auto&... ts) { return (is >> ... >> ts); }; }

template<class T, class U> istream& operator>>(istream& is, pair<T, U>& x) { return apply(variadic_reader(is), x); }
template<class... Ts> istream& operator>>(istream& is, tuple<Ts...>& x) { return apply(variadic_reader(is), x); }
template<class T, size_t N> istream& operator>>(istream& is, array<T, N>& x) { return apply(variadic_reader(is), x); }
template<class T> istream& operator>>(istream& is, vector<T>& r) { return range_read(is, r); }
template<class T> istream& operator>>(istream& is, deque<T>& r) { return range_read(is, r); }
template<class T> istream& operator>>(istream& is, forward_list<T>& r) { return range_read(is, r); }
template<class T> istream& operator>>(istream& is, list<T>& r) { return range_read(is, r); }
template<class T> istream& operator>>(istream& is, optional<T>& o) { o.emplace(read<T>(is)); return is; }
// Allows reading bitstrings without whitespace
istream& operator>>(istream& is, vector<bool>& r) { for (size_t i = 0; i < size(r); i++) r[i] = read<char>(is) == '1'; return is; }

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
/*
const int inf = 1e9;
struct Node
{
	Node* l = 0, * r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	i64 sum = 0;
	Node(int lo, int hi):lo(lo), hi(hi) {} // Large interval of -inf
	Node(vi& v, int lo, int hi): lo(lo), hi(hi)
	{
		if (lo + 1 < hi)
		{
			int mid = lo + (hi - lo) / 2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int sum(int L, int R)
	{

	}
	int query(int L, int R)
	{
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x)
	{
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else
		{
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x)
	{
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R)
		{
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else
		{
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push()
	{
		if (!l)
		{
			int mid = lo + (hi - lo) / 2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
		else if (madd)
			l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
	}
};*/


ll rnd()
{
	static uniform_int_distribution<ll> d(MIN<ll>, MAX<ll>);
	return d(randy);
}
struct Node; typedef array<Node*, 2> ann;
//int T = 0; // current version. T++ => next op is persistent.
struct Node
{
	ll p;      // priority
	ann c;   // children
	//int t;     // timestamp
	int n;     // size
	int v;     // value
	ll s;      // sum
	int m;     // min
	int am;    // argmin
	//int l = 0; // lazy value
	Node(int val, ll p): p(p), c{}, n(1), v(val), s(val), m(val), am(0) {}
	Node(int val): Node(val, rnd()) {}
	~Node() { rep(i, 0, 2) delete c[i]; } // breaks persistence
	//void upd(int x) { l += x; v += x; s += (ll)n * x; } // custom
};
// If persistence not needed, just return n.
// Use bump allocator (w/ free list?) for efficiency.
void cp(Node*& n)
{
	//if (n && n->t != T) (n = new Node(*n))->t = T;
}
// If lazy prop not needed, just call cp(n) and return n.
Node* push(Node*& n)
{ // custom; recurse for ST beats
	cp(n); /*if (n && n->l)
	{ // if (has lazy value)
		rep(i, 0, 2) if (cp(n->c[i]), n->c[i])
		{
			n->c[i]->upd(n->l);
		} n->l = 0; // reset lazy value
	}*/ return n;
}
void fix(Node* n)
{ // custom
	int n0 = n->c[0] ? n->c[0]->n : 0;
	n->n = 1; n->s = n->v - n0; // reset sum
	//cerr << "fixing " << n->v << n0 << n->s << endl;
	n->m = n->v - n0;
	n->am = n0;
	rep(i, 0, 2) if (n->c[i])
	{
		int idx = i ? n0 + 1 : 0;
		int m = n->c[i]->m - idx;
		i64 s = n->c[i]->s - i64(idx) * n->c[i]->n;
		n->n += n->c[i]->n;
		n->s += s; // update n's sum
		if (m < n->m || i == 0 && m == n->m)
		{
			n->m = m;
			n->am = idx + n->c[i]->am;
		}
	}
	rep(i, 0, 2)
		if (n->c[i]) dassert(n->m <= n->c[i]->m);
}
// p determines which side a node goes on (1 -> right)
template<class P> void split(Node* n, ann& A, P&& p)
{
	if (n)
	{
		bool d = p(push(n)); split(n->c[!d], A, p);
		n->c[!d] = A[d]; fix(A[d] = n);
	}
}
template<class P> auto split(Node* n, P&& p)
{
	ann A{}; split(n, A, p); return make_pair(A[0], A[1]);
}
// 1st node where p is true or nullptr
// Pd: push-down every node
template<bool Pd, class P> Node* upper_bound(Node* n, P&& p)
{
	if (n)
	{
		bool d = p(Pd ? push(n) : n); Node* m = upper_bound(n->c[!d], p);
		if (m || !d) n = m; // m || d for last where !p
	} return n;
}
// p for implicit split/upper_bound (splits < i and >= i)
struct impl
{
	int i;
	impl(int i): i(i) {}
	bool operator()(Node* n)
	{
		int l = n->c[0] ? n->c[0]->n : 0, d = l >= i;
		if (!d) i -= l + 1; return d;
	}
};
Node* join(ann A)
{
	rep(i, 0, 2) if (!A[i]) return A[!i];
	bool d = A[0]->p < A[1]->p;
	Node* n = push(A[!d]); A[!d] = n->c[d];
	n->c[d] = join(A);
	fix(n); return n;
}
Node* join(Node* a, Node* b) { return join({ a, b }); }
template<bool Pd> void each(Node* n, const auto&& f, int d = 0)
{
	if (Pd ? push(n) : n)
	{
		each<Pd>(n->c[0], forward<decltype(f)>(f), d + 1); f(n, d); each<Pd>(n->c[1], forward<decltype(f)>(f), d + 1);
	}
}
Node* tree(vector<Node*> A)
{ // A's sorted, singleton, nonlazy
	static stack<Node*> S({ 0 }); Node* r;
	for (Node* a : A)
	{
		cp(a); for (r = 0; S.top() && a->p < S.top()->p; S.pop())
			fix(r = S.top());
		a->c[0] = r; if (S.top()) S.top()->c[1] = a; S.push(a);
	} for (r = 0; S.top(); S.pop()) fix(r = S.top()); return r;
}

void go()
{
	int n;
	cin >> n;
	vi32 A(n);
	cin >> A;
	for (int& a : A) a--;

	Node* root = nullptr;
	for (int a : A)
	{
		auto [l, r] = split(root, [a](Node* n) { return n->v > a; });
		Node* nd = new Node(a);
		root = join(join(l, nd), r);
		//each<false>(root, [](Node* n, int d) { cerr << d << ':' << n->v << '_' << n->m << '_' << n->s << ' '; });
		while (root->m < 0)
		{
			//cerr << root->m << '-' << root->am << ' ';
			int i = root->am;
			auto [x, yz] = split(root, impl(i));
			auto [y, z] = split(yz, impl(1));
			dassert(y->n == 1);
			//cerr << y->v << ' ';
			delete y;
			root = join(x, z);
		}
		//cerr << endl;
		cout << root->s << ' ';
		//cerr << a << ":\n";
		//cerr << root->v << endl;
		//each<false>(root, [](Node* n, int d) { cerr << d << ':' << n->v << '_' << n->m << '_' << n->s << ' '; });
		//cerr << endl << endl;
	}
	//cerr << endl;
	cout << endl;

	delete root;


}