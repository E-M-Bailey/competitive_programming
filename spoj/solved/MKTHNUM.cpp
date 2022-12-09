#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

template<class T> constexpr T MAX = numeric_limits<T>::max();
template<class T> constexpr T MIN = numeric_limits<T>::min();

using namespace chrono;
mt19937_64 randy(duration_cast<nanoseconds>(high_resolution_clock::now().time_since_epoch()).count());

/**
 * Author: Evan Bailey
 * Date: 2022-11-01
 * Source: folklore
 * Description: A persistent treap with lazy propagation.
 *  Use a bump allocator for better performance.
 * Time: $O(\log N)$
 * Status: tested
 */

ll rnd() {
	static uniform_int_distribution<ll> d(MIN<ll>, MAX<ll>);
	return d(randy);
}
struct Node; typedef array<Node*, 2> ann;
int T = 0; // current version. T++ => next op is persistent.
struct Node {
	ll p;      // priority
	ann c{};   // children
	int t;     // timestamp
	int n;     // size
	int v;     // value
	int s;      // sum
	int i;
	//int l = 0; // lazy value
	Node(int val, ll p) : p(p), c{}, t(T), v(val), s(val) {}
	Node(int val) : Node(val, rnd()) {}
	//~Node() { rep(i, 0, 2) delete c[i]; } // breaks persistence
	void incr() { v++; s++; } // custom
};
// If persistence not needed, just return n.
// Use bump allocator (w/ free list?) for efficiency.
void cp(Node*& n) {
	if (n && n->t != T) (n = new Node(*n))->t = T;
}
// If lazy prop not needed, just call cp(n) and return n.
Node* push(Node*& n) { // custom; recurse for ST beats
	cp(n); return n;
}
void fix(Node* n) { // custom
	n->n = 1; n->s = n->v; // reset sum
	rep(i, 0, 2) if (n->c[i]) {
		n->n += n->c[i]->n;
		n->s += n->c[i]->s; // update n's sum
	}
}
// p determines which side a node goes on (1 -> right)
template<class P> void split(Node* n, ann& A, P&& p) {
	if (n) {
		bool d = p(push(n)); split(n->c[!d], A, p);
		n->c[!d] = A[d]; fix(A[d] = n);
	}
}
template<class P> auto split(Node* n, P&& p) {
	ann A{}; split(n, A, p); return make_pair(A[0], A[1]);
}
// 1st node where p is true or nullptr
// Pd: push-down every node
template<bool Pd, class P> Node* upper_bound(Node* n, P&& p) {
	if (n) {
		bool d = p(Pd ? push(n) : n); Node* m = upper_bound(n->c[!d], p);
		if (m || !d) n = m; // m || d for last where !p
	} return n;
}
// p for implicit split/upper_bound (splits < i and >= i)
struct impl {
	int i;
	impl(int i) : i(i) {}
	bool operator()(Node* n) {
		int l = n->c[0] ? n->c[0]->n : 0, d = l >= i;
		if (!d) i -= l + 1; return d;
	}
	bool operator()(Node* n1, Node* n2) {
		int l1 = n1->c[0] ? n1->c[0]->s : 0;
		int l2 = n2->c[0] ? n2->c[0]->s : 0;
		//cerr << "Comparing " << n1->i << ' ' << l1 << " with " << n2->i << ' ' << l2 << ", i=" << i << endl;
		int l = l2 - l1;
		bool v = n2->v - n1->v;
		bool d = l > i || (l == i && v);
		if (!d) i -= l + v; return d;
	}
};
Node* join(ann A) {
	rep(i, 0, 2) if (!A[i]) return A[!i];
	bool d = A[0]->p < A[1]->p;
	Node* n = push(A[!d]); A[!d] = n->c[d];
	n->c[d] = join(A); fix(n); return n;
}
Node* join(Node* a, Node* b) { return join({ a, b }); }
template<bool Pd, class F> void each(Node* n, const F&& f) {
	if (Pd ? push(n) : n) {
		each(n->c[0], f); f(n); each(n->c[1], f);
	}
}
Node* tree(vector<Node*> A) { // A's sorted, singleton, nonlazy
	static stack<Node*> S({ 0 }); Node *r;
	for (Node* a : A) {
		cp(a); for (r = 0; S.top() && a->p < S.top()->p; S.pop())
			fix(r = S.top());
		a->c[0] = r; if (S.top()) S.top()->c[1] = a; S.push(a);
	} for (r = 0; S.top(); S.pop()) fix(r = S.top()); return r;
}


template<bool Pd, class P> pair<Node*, Node*> upper_bound2(Node* n1, Node* n2, P&& p) {
	if (n1) {
		bool d = Pd ? p(push(n1), push(n2)) : p(n1, n2); auto M = upper_bound2<Pd>(n1->c[!d], n2->c[!d], p);
		
		if (M.first || !d) tie(n1, n2) = M; ; // m || d for last where !p
	} return {n1, n2};
}

int main() {
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit); // remove for weird input formats

	int n, m;
	cin >> n >> m;
	vi A(n);
	for (int& a : A)
		cin >> a;
	vi ICC = A;
	sort(all(ICC));
	ICC.resize(n);
	unordered_map<int, int> CC;
	CC.reserve(n);
	for (int i = 0; i < ICC.size(); i++)
		CC[ICC[i]] = i;
	for (int& a : A)
		a = CC[a];
	vector<Node*> N(n);
	for (int i = 0; i < n; i++) {
		N[i] = new Node(0);
		N[i]->i = ICC[i];
	}
	vector<Node*> R(n + 1);
	Node* r = R[0] = tree(N), *s, *t;
	N.clear();

	for (T++; T <= n; T++) {
		int j = A[T - 1];
		tie(r, s) = split(r, impl(j));
		tie(s, t) = split(s, impl(1));
		push(s)->incr();
		R[T] = r = join(r, join(s, t));
	}
	while (m--) {
		int i, j, k;
		cin >> i >> j >> k;
		Node *r1 = R[i - 1], *r2 = R[j];
		Node* n = upper_bound2<0>(r1, r2, impl(k - 1)).first;
		cout << n->i << endl;
	}
}
// test: g++ -DDEBUG -g -O2 -std=gnu++17 -static <file> && ./a.out