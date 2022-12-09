#ifndef LP_TREAP_H_INCLUDED
#define LP_TREAP_H_INCLUDED

#ifndef TEMPLATE_H_INCLUDED
#include "template.h"
#endif // TEMPLATE_H_INCLUDED

// Lazy-prop, optionally persistent implicit treap forest
// p l k i a d: only for pers, lazy, key, index, accum, del ops
// p and d are mutually exclusive
int rnd() {
	static uniform_int_distribution<int> d(INT_MIN, INT_MAX - 1);
	return d(randy);
}
struct B { unsigned r : 31, d : 1; };
struct LPTreap {
	typedef int K; /*k*/ typedef int V;
	typedef int64_t S; static constexpr S SID = 0; //a
	typedef int L; static constexpr L LID = 0; //l
	// prior time(p) size(i) children val sum(a) lazy(l) key(k)
	struct N { int p, t, n; aii c; V v; S s; L l; K k; };
	// nodes stack free(d) time(p)
	vector<N> T; vector<B> R; vi F; int t = 0;
	int p(int i) { return i < 0 ? INT_MAX : T[i].p; }
	S s(int i) { return i < 0 ? SID : T[i].s; } //a
	int w(int i) { return i < 0 ? t : T[i].t; } //p
	int n(int i) { return i < 0 ? 0 : T[i].n; } //i
	L l(int i) { return i < 0 ? LID : T[i].l; } //l
	// Custom:
	bool cmp(K l, K r) { return l < r; } //k
	void f(N& n) { n.s = n.v + s(n.c[0]) + s(n.c[1]); } //a
	void g(N& n) { n.v += n.l; n.s += n.n * n.l; } //l
	void h(N& p, N& c, bool d) { c.l += p.l; } //l
	bool l(N& n) { return n.l != LID; } //l
	
	LPTreap& p() { t++; return *this; } //p: Makes next op pers
	void undo() { //p
		t--; while (sz(T) && T.back().t > t) { T.pop_back(); }
	}
	void upd(int r) { //a|i if neither a nor i, delete upd's body
		if (r >= 0) {
			f(T[r]); //a
			T[r].n = 1 + n(T[r].c[0]) + n(T[r].c[1]); //i
		}
	}
	int mk(N n) {
		n.t = t; /*p*/ int r = sz(T);
		if (sz(F)) { T[r = F.back()] = n; F.pop_back(); } //d
		else T.push_back(n); f(T[r]); /*a*/ return r;
	}
	int mk(K k, V v) { // change based on deleted fields
		return mk({ rnd(), t, 1, { -1, -1 }, v, SID, LID, k });
	}
	//c: if persistence unneeded, just return r
	int c(int& r) { return w(r) == t ? r : (r = mk(T[r])); } //p
	int pd(int& r) { //l: if not lazy, just return c(r)
		if (c(r) >= 0 && l(T[r])) {
			rep(d, 0, 2) if (c(T[r].c[d]) >= 0)
				h(T[r], T[T[r].c[d]]); g(T[r]); T[r].l = LID;
		} return r;
	}
	B pop() { B b = R.back(); R.pop_back(); return b; }
	void push(int r, bool d) { R.push_back({ r, d }); }
	template<bool Pd> void rk(int r, K x) { //k
		while (pd(r) >= 0) {
			K y = T[pd(r)].k; bool d = cmp(y, x), e = !cmp(x, y);
			push(r, Pd ? d : e); if (!d && e) break; r = T[r].c[d];
		}
	}
	template<bool Pd> void ri(int r, int x) { //i
		while (pd(r) >= 0) {
			int y = n(T[r].c[0]); bool d = y < x, e = y <= x;
			push(r, Pd ? d : e); if (y == x) break;
			r = T[r].c[d]; if (d) x -= y + 1;
		}
	}
	void rj(aii a) {
		while (max(a[0], a[1]) >= 0) {
			bool d = p(a[0]) > p(a[1]); push(pd(a[d]), d);
			a[d] = T[a[d]].c[!d];
		}
	}
	pii spt() { // split
		if (!sz(R)) return { -1, -1 }; aii a{ -1, -1 };
		B b = R.back(); a[b.d] = T[b.r].c[b.d]; do {
			b = pop(); T[b.r].c[b.d] = a[!b.d]; upd(a[!b.d] = b.r);
		} while (sz(R)); return { a[0], a[1] };
	}
	template<bool d/*x goes right*/>
	pii sptk(int r, K x) { rk<d>(r, x); return spt(); } //k
	template<bool d/*x goes right*/>
	pii spti(int r, int x) { ri<d>(r, x); return spt(); } //i
	int jn(int r, int s) { // join
		rj({ r, s }); r = -1; while (sz(R)) {
			B b = pop(); T[b.r].c[!b.d] = r; upd(r = b.r);
		} return r;
	}
	template<bool d/*right*/> int xtr(int r) { // extremum
		if (r >= 0) while (T[pd(r)].c[d] >= 0) r = T[r].c[d];
		return r;
	}
	template<bool d/*right*/> int bnd() { // bound
		int s = -1; while (sz(R)) {
			B b = pop(); s = b.r; if (b.d ^ d) break;
		} R.clear(); return s;
	}
	template<bool d/*right*/, bool Pd/*x goes right*/>
	int bndk(int r, K x) { rk<Pd>(r, x); return bnd<d>(); } //k
	template<bool d/*right*/, bool Pd/*x goes right*/>
	int bndi(int r, int x) { ri<Pd>(r, x); return bnd<d>(); } //i
	int getk(int r, K x) { //k
		r = bndk<1, 1>(r, x); return r < 0 || T[r].k == x ? -1 : r;
	}
	int geti(int r, int x) { //i
		return 0 <= x && x < T[r].n ? bndi<1, 1>(r, x) : -1;
	}
	int indexof(int r, K x) { //k&i
		int i = 0; while (pd(r) >= 0) {
			bool d = !cmp(x, T[r].k); i += d * (n(T[r].c[0]) + 1);
			if (T[r].k == x) return i; r = T[r].c[d];
		} return -1;
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
	void del(int r) { //d
		io<0>(r, [&](int i) { F.push_back(i); });
	}
};

#endif