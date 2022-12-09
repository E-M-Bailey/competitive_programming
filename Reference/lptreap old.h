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
	typedef int T; static constexpr T TID = 0; //k
	typedef int U; static constexpr U UID = 0; //UID: a
	typedef int L; static constexpr L LID = 0; //l
	// prior timestamp(p) size(i) children val sum(a) lazy(l)
	vi P, W, N; vector<aii> C; vector<U> V, S; vector<L> Z;
	// key(k) stack time(p)
	vector<T> K; vector<B> R; int t = 0;
	int p(int i) { return i < 0 ? INT_MAX : P[i]; }
	U s(int i) { return i < 0 ? UID : S[i]; } //a
	int w(int i) { return i < 0 ? t : W[i]; } //p
	int n(int i) { return i < 0 ? 0 : N[i]; } //i
	bool cmp(T l, T r) { return l < r; } //k
	void f(int i, int j, int k) { S[i] = V[i] + s(j) + s(k); }//a
	void g(int i) { V[i] += Z[i]; S[i] += N[i] * Z[i]; } //l
	void h(int i, int j) { Z[j] += Z[i]; } //l
	bool l(L l) { return l != LID; } //l
	LPTreap& p() { t++; return *this; } // Makes next op pers (p)
	void res(int n) { // optional
		P.reserve(n); W.reserve(n); N.reserve(n); C.reserve(n);
		V.reserve(n); S.reserve(n); Z.reserve(n); K.reserve(n);
	}
	void undo() { //p
		t--; while (sz(W) && W.back() > t) {
			P.pop_back(); W.pop_back(); N.pop_back(); C.pop_back();
			V.pop_back(); S.pop_back(); Z.pop_back(); K.pop_back();
		}
	}
	int mk(int p, aii c, T k, U v, U s, L z = LID, int n = 1) {
		P.push_back(p); W.push_back(t); N.push_back(n);
		C.push_back(c); V.push_back(v); S.push_back(s);
		Z.push_back(z); K.push_back(k); return sz(P) - 1;
	}
	int mk(T k, U v) { return mk(rnd(), { -1, -1 }, k, v, v); }
	int c(int& r) { //p: if persistence unneeded, just return r
		return w(r) == t ? r
			: (r = mk(P[r], C[r], K[r], V[r], S[r], Z[r], N[r]));
	}
	int pd(int& r) { //l: if not lazy, just return c(r)
		if (c(r) >= 0 && l(Z[r])) {
			rep(d, 0, 2) if (c(C[r][d]) >= 0) h(r, C[r][d]);
			g(r); Z[r] = LID;
		} return r;
	}
	void upd(int r) { //a,i: if neither a nor i, delete fn body
		if (r >= 0) {
			f(r, C[r][0], C[r][1]); //a
			N[r] = 1 + n(C[r][0]) + n(C[r][1]); //i
		}
	}
	B pop() { B a = R.back(); R.pop_back(); return a; }
	void push(int r, bool d) { R.push_back({ r, d }); }
	template<bool Pd/*x goes right*/> void rk(int r, T x) { //k
		while (pd(r) >= 0) {
			bool d = Pd ? cmp(K[pd(r)], x) : !cmp(x, K[pd(r)]);
			push(r, d); r = C[r][d];
		}
	}
	template<bool Pd/*x goes right*/> void ri(int r, int x) { //i
		while (pd(r) >= 0) {
			int y = n(C[r][0]); bool d = Pd ? y < x : y <= x;
			push(r, d);	r = C[r][d]; if (d) x -= y + 1;
		}
	}
	void rj(aii a) {
		while (max(a[0], a[1]) >= 0) {
			bool d = p(a[0]) > p(a[1]); push(pd(a[d]), d);
			a[d] = C[a[d]][!d];
		}
	}
	pii spt() { // split
		aii a{ -1, -1 }; while (sz(R)) {
			auto [r, d] = pop(); C[r][d] = a[!d]; upd(a[!d] = r);
		} return { a[0], a[1] };
	}
	template<bool d/*x goes right*/>
	pii sptk(int r, T x) { rk<d>(r, x); return spt(); } //k
	template<bool d/*x goes right*/>
	pii spti(int r, int x) { ri<d>(r, x); return spt(); } //i
	int jn(int r, int s) { // join
		rj({ r, s }); r = -1; while (sz(R)) {
			auto [a, d] = pop(); C[a][!d] = r; upd(r = a);
		} return r;
	}
	template<bool d/*right*/> int xtr(int r) { // extremum
		if (r >= 0) while (C[r][d] >= 0) r = C[r][d]; return r;
	}
	template<bool d/*right*/> int bnd() { // bound
		int s = -1; while (sz(R)) {
			auto [r, e] = pop(); s = r; if (e ^ d) break;
		} R.clear(); return s;
	}
	template<bool d/*right*/, bool Pd/*x goes right*/>
	int bndk(int r, T x) { rk<Pd>(r, x); return bnd<d>(); } //k
	template<bool d/*right*/, bool Pd/*x goes right*/>
	int bndi(int r, int x) { ri<Pd>(r, x); return bnd<d>(); } //i
	int getk(int r, T x) { //k
		r = bndk<1, 1>(r, x); return r < 0 || K[r] == x ? -1 : r;
	}
	int geti(int r, int x) { //i
		return 0 <= x && x < N[r] ? bndi<1, 1>(r, x) : -1;
	}
	int indexof(int r, T x) { //k and i
		int i = 0; while (pd(r) >= 0) {
			bool d = !cmp(x, K[r]); i += d * (n(C[r][0]) + 1);
			if (K[r] == x) return i; r = C[r][d];
		} return -1;
	}
	int tree(const vi& A) { // A: sorted non-lazy isolated nodes
		int r, p; for (int a : A) {
			c(a); r = -1; while (sz(R) && P[a] < P[R.back().r])
				upd(r = pop().r);
			C[a][0] = r; p = sz(R) ? R.back().r : -1; upd(a);
			push(a, 0); if (p >= 0) C[p][1] = a;
		} r = -1; while (sz(R)) upd(r = pop().r); return r;
	}
	template<class F> void io(int& r, const F& f) { // inorder
		if (pd(r) >= 0) { io(C[r][0], f); f(r); io(C[r][1], f); }
	}
};

#endif