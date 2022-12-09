#include <bits/stdc++.h>
using namespace std;

// Link-Cut Tree
struct LCT {
	//typedef int T;
	int n;
	vector<int> P, PP;
	vector<bool> R;
	vector<array<int, 2>> C;
	LCT(int n) :
		n(n),
		P(n, -1),
		PP(n, -1),
		R(n, false),
		C(n, {-1, -1}) {}
	//int& c(int v, bool d) {return C[v][d ^ R[v]];}
	bool dir(int u, int v) {return C[u][1] == v;}
	void rev(int v) {if (v >= 0) R[v] = !R[v];}
	void push_down(int v) {
		if (R[v]) {
			rev(C[v][0]);
			rev(C[v][1]);
			swap(C[v][0], C[v][1]);
			R[v] = false;
		}
	}
	void pull_down(int v) {
		if (v < 0) return;
		vector<int> S;
		S.push_back(v);
		while (P[S.back()] >= 0)
			S.push_back(P[S.back()]);
		while (!S.empty()) {
			int w = S.back();
			S.pop_back();
			push_down(w);
		}
	}
	// R should be propagated first
	void rot(int v) {
		assert (v >= 0);
		int u = P[v];
		if (u < 0) return;
		bool r = dir(u, v);
		bool l = !r;

		int g = P[u];
		if (g >= 0)
			C[g][dir(g, u)] = v;
		P[v] = g;

		int w = C[v][l];
		if (w >= 0)
			P[w] = u;
		C[u][r] = w;

		C[v][l] = u;
		P[u] = v;

		swap(PP[u], PP[v]);
	}
	void splay(int v) {
		assert(v >= 0);
		pull_down(v);
		int u;
		while ((u = P[v]) >= 0) {
			int g = P[u];
			if (g < 0) {
				rot(v);
				return;
			}
			rot(dir(g, u) == dir(u, v) ? u : v);
			rot(v);
		}
	}
	void access(int v) {
		splay(v);
		int w0 = C[v][1];
		C[v][1] = -1;
		if (w0 >= 0) {
			P[w0] = -1;
			PP[w0] = v;
		}
		int u;
		while ((u = PP[v]) >= 0) {
			splay(u);
			int w = C[u][1];
			C[u][1] = v;
			P[v] = u;
			PP[v] = -1;
			if (w >= 0) {
				P[w] = -1;
				PP[w] = u;
			}
			rot(v);
		}
	}
	void mkRoot(int v) {
		access(v);
		rev(v);
	}
	int rootOf(int v) {
		access(v);
		int r = v;
		while (C[r][0] >= 0) {
			r = C[r][0];
			push_down(r);
		}
		splay(r);
		return r;
	}
	bool connect(int u, int v) {
		int rv = rootOf(v);
		if (rootOf(u) == rv)
			return false;
		assert(rv == v);
		PP[v] = u;
		return true;
	}
	bool checkEdge(int u, int v) {
		access(u);
		splay(v);
		return C[v][0] < 0 && PP[v] == u;
	}
	bool disconnect(int u, int v) {
		if (!checkEdge(u, v))
			return false;
		PP[v] = -1;
		return true;
	}
	bool urConnect(int u, int v) {
		mkRoot(v);
		/*#ifdef DEBUG
				cerr << "mkRoot(" << v << "):\n";
				dbg();
				cerr << endl;
		#endif*/
		//cerr << "roots: " << rootOf(u) << ' ' << rootOf(v) << endl;
		if (rootOf(u) == v)
			return false;
		PP[v] = u;
		return true;
	}
	bool urCheckEdge(int u, int v) {
		return checkEdge(u, v) || checkEdge(v, u);
	}
	bool urDisconnect(int u, int v) {
		return disconnect(u, v) || disconnect(v, u);
	}
	bool connected(int u, int v) {
		return rootOf(u) == rootOf(v);
	}
	void dbg() {
#ifdef DEBUG
		for (int i = 0; i < n; i++)
			cerr << i << '(' << R[i] << "): " << P[i] << ' ' << C[i][0] << ' ' << C[i][1] << " -> " << PP[i] << endl;
#endif
	}
};

typedef long double T;

const T EPS = 5e-7l;

struct ast {
	array<T, 3> X, V;
};

struct quad {
	T a, b, c;
	T eval(T t) const {
		return (a * t + b) * t + c;
	}
	T derv(T t) const {
		return 2 * a * t + b;
	}
	vector<T> oddZeros() {
		if (a) {
			T d = b * b - 4 * a * c;
			if (d <= 0)
				return {};
			else {
				d = sqrt(d);
				return {(-b - d) / (2 * a), (-b + d) / (2 * a)};
			}
		} else if (b)
			return {-c / b};
		else
			return {};

	}
	friend vector<T> oddIsect(const quad& f, const quad& g) {
		return quad{f.a - g.a, f.b - g.b, f.c - g.c}.oddZeros();
	}
};

struct event {
	T t;
	int i, j, k, l;
	friend bool operator<(const event& l, const event& r) {
		return l.t < r.t;
	}
};

int main(int argc, char* argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}

	int tc = 0;
	int n;
	while (cin >> n) {
		vector<ast> A(n);
		for (auto& [X, V] : A) {
			for (auto& x : X) cin >> x;
			for (auto& v : V) cin >> v;
		}
		vector<vector<quad>> F(n);
		for (int i = 0; i < n; i++) {
			F[i].resize(i, {0, 0, 0});
			for (int j = 0; j < i; j++)
				for (int d = 0; d < 3; d++) {
					T dx = A[i].X[d] - A[j].X[d], dv = A[i].V[d] - A[j].V[d];
					F[i][j].a += dv * dv;
					F[i][j].b += 2 * dx * dv;
					F[i][j].c += dx * dx;
				}
		}

		vector<event> E;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++) {
				for (int k = 0; k < i; k++)
					for (int l = 0; l < k; l++)
						for (T t : oddIsect(F[i][j], F[k][l]))
							if (t >= 0)
								E.push_back({t, i, j, k, l});
				for (int l = 0; l < j; l++)
					for (T t : oddIsect(F[i][j], F[i][l]))
						if (t >= 0)
							E.push_back({t, i, j, i, l});
			}
		for (auto& [t, i, j, k, l] : E) {
			if (F[i][j].derv(t) < F[k][l].derv(t)) {
				swap(i, k);
				swap(j, l);
			}
		}
		sort(E.begin(), E.end());
		/*#ifdef DEBUG
				cerr << E.size() << endl;
				for (auto [t, i, j, k, l] : E)
					cerr << t << ' ' << i << ' ' << j << ' ' << k << ' ' << l << endl;
		#endif*/
		const auto at0 = [&](pair<int, int> L, pair<int, int> R) {
			auto [i, j] = L;
			auto [k, l] = R;
			return F[i][j].eval(0) > F[k][l].eval(0);
		};

		LCT lct(n);
		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(at0)> Q(at0);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
				Q.push({i, j});
		//cerr << endl;
		//lct.dbg();
		while (!Q.empty()) {
			auto [i, j] = Q.top();
			Q.pop();
			bool succ = lct.urConnect(i, j);
			//if (succ)
			//	cerr << "init " << i << ' ' << j << endl;
			/*#ifdef DEBUG
						cerr << endl;
						cerr << i << ' ' << j << endl;
						lct.dbg();
						cerr << succ << endl;
			#endif*/
		}
		/*if (n == 4) {
		    cerr << F[3][0].a << ' ' << F[3][0].b << ' ' << F[3][0].c << endl;
		    cerr << F[3][1].a << ' ' << F[3][1].b << ' ' << F[3][1].c << endl;
		}*/
		int idx = 0;
		int ans = 1;
		//int ct = 0;
		while (idx < E.size()) {
			T t0 = E[idx].t;
			//bool cur = false;
			do {
				//ct++;
				auto [t, i, j, k, l] = E[idx];
				//bool kl = lct.urCheckEdge(k, l);
				//bool db = i == 3 && j == 0 && k == 3 && l == 1;
				//lct.dbg();
				//cerr << i << ' ' << j << ' ' << k << ' ' << l << ' ' << kl << endl << endl;
				//cerr << k << ' ' << l << ' ' << lct.checkEdge(k, l) << endl;
				//lct.dbg();
				//cerr << lct.checkEdge(l, k) << endl;
				//if (db && lct.urCheckEdge(k, l))
				//    cerr << "nooo!" << endl;
				if (lct.urCheckEdge(k, l) || !lct.urDisconnect(i, j))
					continue;
				//if (lct.urCheckEdge(i, j)) {
				//	cerr << "help " << i << ' ' << j << endl;
				//	exit(-1);
				//}
				//if (lct.ur
				//if (db)
				//	cerr << ' ' << (lct.rootOf(k) == lct.rootOf(l)) << endl;
				if (lct.rootOf(k) == lct.rootOf(l)) {
                    lct.urConnect(i, j);
					//if (!lct.urConnect(i, j)) {
						//		cerr << i << ' ' << j << endl;
					//	exit(-1);
					//}
				} else {
				    lct.urConnect(k, l);
					//if (!lct.urConnect(k, l)) {
						//		cerr << '-' << k << ' ' << j << endl;
					//	exit(-1);
					//}
					//	cerr << "switchting " << i << ' ' << j << "->" << k << ' ' << l << " @ " << t << endl;
					//cur = true;
					ans++;
				}
			} while (++idx < E.size() && E[idx].t - t0 <= EPS);
			//ans += cur;
		}
		//cerr << ct << ' ' << E.size() << endl;
		cout << "Case " << ++tc << ": " << ans << endl;
	}

}
