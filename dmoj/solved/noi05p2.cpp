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

ll rnd() {
	static uniform_int_distribution<ll> d(MIN<ll>, MAX<ll>);
	return d(randy);
}
struct Node; typedef array<Node*, 2> ann;
int T = 0; // current version. T++ => next op is persistent.
struct Node {
	ll p;      // priority
	ann c;   // children
	int t;     // timestamp
	int n;     // size
	int v;     // value
	int s, ls, rs, ms;      // sum
	bool r = 0; int l = INT_MIN; // lazy value
	Node(int val) : p(rnd()), c{}, t(T), v(val), s(val), ls(val), rs(val), ms(val) {}
	~Node() { rep(i, 0, 2) delete c[i]; } // breaks persistence
	void set(int x) {
		l = x;
		v = x;
		s = n * x;
		ls = rs = ms = max(v, s);
	}
	void rev() {
		r ^= 1;
		swap(c[0], c[1]);
		swap(ls, rs);
	}
};
// If persistence not needed, just return n.
// Use bump allocator for efficiency.
void cp(Node*& n) {
	if (n && n->t != T) (n = new Node(*n))->t = T;
}
Node* push(Node*& n) { // custom; recurse for ST beats
	if (n && (n->r || n->l != INT_MIN)) { // if (has lazy value)
		cp(n); rep(i, 0, 2) if (cp(n->c[i]), n->c[i]) {
			Node* c = n->c[i];
			if (n->l != INT_MIN)
				c->set(n->l);
			else if (n->r)
				c->rev();
		} n->l = INT_MIN; n->r = 0; // reset lazy value
	} return n;
}
tuple<int, int, int, int> get(Node* n) {
	if (n) return { n->s, n->ls, n->rs, n->ms };
	else return { 0, INT_MIN, INT_MIN, INT_MIN };
}
void fix(Node* n) { // custom
	n->n = 1; n->s = n->v; // reset sum
	rep(i, 0, 2) if (n->c[i]) {
		n->n += n->c[i]->n;
		n->s += n->c[i]->s; // update n's sum
	}
	auto [ls, lls, lrs, lms] = get(n->c[0]);
	auto [rs, rls, rrs, rms] = get(n->c[1]);
	lrs = max(lrs, 0);
	rls = max(rls, 0);
	n->ls = max(lls, ls + n->v + rls);
	n->rs = max(rrs, rs + n->v + lrs);
	n->ms = max(max(lms, rms), lrs + n->v + rls);
}
// p determines which side a node goes on (1 -> right)
template<class P> void split(Node* n, ann& A, const P& p) {
	if (n) {
		bool d = p(push(n)); split(n->c[!d], A, p);
		n->c[!d] = A[d]; fix(A[d] = n);
	}
}
template<class P> auto split(Node* n, const P& p) {
	ann A{}; split(n, A, p); return make_pair(A[0], A[1]);
}
// splits by indices into < i and >= i.
auto split(Node* n, int i) {
	return split(n, [&](Node* n) -> bool {
		int l = n->c[0] ? n->c[0]->n : 0, d = l >= i;
		if (!d) i -= l + 1; return d;
		});
}
Node* join(ann A) {
	rep(i, 0, 2) if (!A[i]) return A[!i];
	bool d = A[0]->p < A[1]->p;
	Node* n = push(A[!d]); A[!d] = n->c[d];
	n->c[d] = join(A); fix(n); return n;
}
Node* join(Node* a, Node* b) { return join({ a, b }); }
template<class F> void each(Node* n, const F& f) {
	if (push(n)) { each(n->c[0], f); f(n); each(n->c[1], f); }
}
Node* tree(vector<Node*> A) { // A's sorted, singleton, nonlazy
	static stack<Node*> S({ 0 }); Node *r;
	for (Node* a : A) {
		cp(a); for (r = 0; S.top() && a->p < S.top()->p; S.pop())
			fix(r = S.top());
		a->c[0] = r; if (S.top()) S.top()->c[1] = a; S.push(a);
	} for (r = 0; S.top(); S.pop()) fix(r = S.top()); return r;
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
	vector<Node*> A(n);
	for (Node*& a : A) {
		int x;
		cin >> x;
		a = new Node(x);
	}
	Node *r = tree(A), *s, *t;
	int i;
	string cmd;
	while (m--) {
		cin >> cmd;
		switch (cmd[2]) {
		case 'S':
			cin >> i >> n;
			A.resize(n);
			for (Node*& a : A) {
				int x;
				cin >> x;
				a = new Node(x);
			}
			s = tree(A);
			tie(r, t) = split(r, i);
			r = join(r, s);
			r = join(r, t);
			break;
		case 'L':
			cin >> i >> n;
			tie(r, s) = split(r, i - 1);
			tie(s, t) = split(s, n);
			r = join(r, t);
			delete s;
			break;
		case 'K':
			cin >> i >> n;
			tie(r, s) = split(r, i - 1);
			tie(s, t) = split(s, n);
			int c;
			cin >> c;
			s->set(c);
			r = join(r, s);
			r = join(r, t);
			break;
		case 'V':
			cin >> i >> n;
			tie(r, s) = split(r, i - 1);
			tie(s, t) = split(s, n);
			s->rev();
			r = join(r, s);
			r = join(r, t);
			break;
		case 'T':
			cin >> i >> n;
			tie(r, s) = split(r, i - 1);
			tie(s, t) = split(s, n);
			cout << (s ? s->s : 0) << '\n';
			r = join(r, s);
			r = join(r, t);
			break;
		case 'X':
			cout << r->ms << endl;
			break;
		}
	}
}
// test: g++ -DDEBUG -g -O2 -std=gnu++17 -static <file> && ./a.out