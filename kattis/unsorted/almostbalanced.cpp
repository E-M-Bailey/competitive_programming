#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

typedef long long ll;

mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());

template<class T> constexpr T MAX = numeric_limits<T>::max();
template<class T> constexpr T MIN = numeric_limits<T>::min();

#define rep(i, a, b) for (decltype((a) + (b)) i = (a); i < (b); ++i)

ll rnd()
{
	static uniform_int_distribution<ll> d(MIN<ll>, MAX<ll>);
	return d(randy);
}
struct Node;
typedef array<Node*, 2> ann;
struct Node
{
	ll p; // priority
	ann c{}; // children
	int n = 0; // size
	int r, l; // key
	int v; // value
	ll m; // min
	int am; // argmin
	int l = 0; // lazy value
	Node(int kr, int kl, int val, ll p): p(p), c{}, r(kr), l(kl), v(val), m(val), am(0) {}
	Node(int kr, int kl, int val): Node(kr, kl, val, rnd()) {}
	//∼Node() { rep( i , 0, 2) delete c [ i ] ; } // breaks persistence
	void upd(int x) { l += x; v += x; m += x; } // custom
};
// I f persistence not needed, just return n.
// Use bump al locator (w/ free l i s t ?) for ef f iciency .
void cp(Node*& n) {}
// I f lazy prop not needed, just cal l cp(n) and return n.
Node* push(Node*& n)
{ // custom; recurse for ST beats
	cp(n);
	if (n && n->l)
	{ // i f (has lazy value)
		rep(i, 0, 2) if (cp(n->c[i]), n->c[i])
		{
			n->c[i]->upd(n->l);
		} n->l = 0; // reset lazy value
	} return n;
}
void fix(Node* n)
{ // custom
	int n0 = n->c[0] ? n->c[0]->n : 0;
	n->n = 1; n->m = n->v; n->am = n0; // reset sum
	rep(i, 0, 2) if (n->c[i])
	{
		n->n += n->c[i]->n;
		int off = i ? n0 + 1 : 0;
		int a = n->c[i]->m, b = n->m;
		if (i ? a < b : a <= b)
		{
			n->m = a;
			n->am = n->c[i]->am + off;
		}
	}
}
// p determines which side a node goes on (1 −> right )
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
// 1st node where p is true or nul lptr
// Pd: push−down every node
template<bool Pd, class P> Node* upper_bound(Node* n, P&& p)
{
	if (n)
	{
		bool d = p(Pd ? push(n) : n);
		Node* m = upper_bound(n->c[!d], p);
		if (m || !d) n = m; // m | | d for last where !p
	} return n;
}
// p for impl icit spl i t/upper bound ( spl i t s < i and >= i )
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
	n->c[d] = join(A); fix(n); return n;
}
Node* join(Node* a, Node* b) { return join({ a, b }); }
template<bool Pd, class F> void each(Node* n, const F&& f)
{
	if (Pd ? push(n) : n)
	{
		each(n->c[0], f); f(n); each(n->c[1], f);
	}
}
Node* tree(vector<Node*> A)
{ // A’ s sorted , singleton , nonlazy
	static stack<Node*> S({ 0 }); Node* r;
	for (Node* a : A)
	{
		cp(a); for (r = 0; S.top() && a->p < S.top()->p; S.pop())
			fix(r = S.top());
		a->c[0] = r; if (S.top()) S.top()->c[1] = a; S.push(a);
	} for (r = 0; S.top(); S.pop()) fix(r = S.top()); return r;
}

struct lim
{
	int l, r, x;
	Node* nd;
	lim(int L, int R, int V): l(L - 1), r(R), x(V / 2) {}
	friend bool operator<(const lim& a, const lim& b)
	{
		if (a.l != b.l)
			return a.l < b.l;
		return a.r < b.r;
	}
};

void ins(Node*& T, Node* n)
{
	if (n)
	{
		auto [a, b] = split(T, [n](Node* nd) { return make_pair(nd->r, nd->l) > make_pair(n->r, n->l); });
		T = join(join(a, n), b);
	}
}

void ers_all(Node*& T, int l, int r)
{
	auto [ab, c] = split(T, [l, r](Node* nd) { return make_pair(nd->r, nd->l) > make_pair(r, l); });
	auto [a, b] = split(ab, [l, r](Node* nd) { return make_pair(nd->r, nd->l) >= make_pair(r, l); });
	T = join(a, b);
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, m;
	cin >> n >> m;

	deque<lim> L0, L1a, L1b;

	while (m--)
	{
		bool t;
		int l, r, v;
		cin >> t >> l >> r >> v;
		(t ? L1a : L0).emplace_back(l, r, v);
	}
	sort(begin(L0), end(L0));
	sort(begin(L1a), end(L1a));
	int m0 = (int)size(L0), m1 = (int)size(L1a);
	L1b = L1a;

	vector<bool> S(n);
	for (int i = 1; i < n; i += 2)
		S[i] = 1;

	vector<Node> N0, N1;
	N0.reserve(m0);
	N1.reserve(m1);
	for (auto& [l, r, x, nd] : L0)
	{
		N0.emplace_back(r, x);
		nd = &N0.back();
	}
	for (auto& [l, r, x, nd] : L1a)
	{
		N1.emplace_back(r, x);
		nd = &N1.back();
	}

	Node* T0 = nullptr;
	Node* T1 = nullptr;
	int nz = 0;

	for (int i = 0; i < n; i++)
	{
		T0 = split(T0, [i](Node* n) { return n->r > i; }).second;
		while (!L0.empty() && L0.front().l == i)
		{
			ins(T0, L0.front().nd);
			L0.pop_front();
		}
		if (nz == i)
			nz++;
		while (nz < n && S[nz])
			nz++;
		while (!L1b.empty() && L1b.front().l < nz)
		{
			ins(T1, L1b.front().nd);
			L1b.pop_front();
		}
		while (!L1a.empty() && L1a.front().l == i)
		{
			ers_all(T1, L1a.front().l, L1a.front().r);
			L1a.pop_front();
		}
		T1 = split(T1, [nz](Node* n) { return n->r > nz; }).second;
		if (S[i])
		{
			if (!T0 || T0->m > 1)
			{
				T0->upd(-1);
				S[i] = 0;
			}
			else
			{
				auto [a, b] = split(T0, [nz](Node* n) { return n->r >= nz; });

			}
		}
	}
}