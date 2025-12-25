#include <bits/stdc++.h>
using namespace std;

struct seg {
	int l, r, y;
	friend bool operator<(const seg& l, const seg& r) {
		if (l.y != r.y)
			return l.y < r.y;
        return l.l < r.l;
	}
};

int& rup2(int& n) {
	--n;
	for (int i = 1; i < 32; i *= 2)
		n |= n >> i;
	return ++n;
}

struct PTree {
	typedef int T;
	static constexpr T UNIT = 0;
	int n = 0;
	vector<array<int, 2>> CH;
	vector<T> S;
	T f(T l, T r) {return l + r;}
	T s(int v) {return v < 0 ? UNIT : S[v];}
	int mkNode(T val, int l, int r) {
		CH.push_back({l, r});
		S.push_back(val);
		return n++;
	}
	int mkNode(int l, int r) {return mkNode(f(s(l), s(r)), l, r);}
	int mkNode(T val = UNIT) {return mkNode(val, -1, -1);}
	// L.size() should be a power of 2
	int mkTree(const vector<T>& L) {
		queue<int> Q;
		for (T l : L)
			Q.push(mkNode(l));
		while (Q.size() > 1) {
			int a = Q.front();
			Q.pop();
			int b = Q.front();
			Q.pop();
			Q.push(mkNode(a, b));
		}
		return Q.front();
	}
	T query(int v, int lo, int hi, int nlo, int nhi) {
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (lo >= hi)
			return UNIT;
		if (lo == nlo && hi == nhi)
			return s(v);
		int mid = (nlo + nhi) / 2;
		T L = query(CH[v][0], lo, hi, nlo, mid);
		T R = query(CH[v][1], lo, hi, mid, nhi);
		return f(L, R);
	}
	T query(int root, int lo, int hi, int m) {
		return query(root, lo, hi, 0, m);
	}
	template<class F>
	int update(int v, const F& f, int i, int nlo, int nhi) {
		if (i < nlo || i >= nhi)
			return v;
		if (nlo + 1 == nhi)
			return mkNode(f(s(v)));
		int mid = (nlo + nhi) / 2;
		int L = update(CH[v][0], f, i, nlo, mid);
		int R = update(CH[v][1], f, i, mid, nhi);
		return mkNode(L, R);
	}
	template<class F>
	int update(int root, const F& f, int i, int m) {
		return update(root, f, i, 0, m);
	}
};

const array<pair<int, int>, 4> DIR{
	pair<int, int>{0, 1},
	pair<int, int>{1, 0},
	pair<int, int>{0, -1},
	pair<int, int>{-1, 0}
};

void mirr(int& d, bool tlbr) {
	d = tlbr ? d ^ 1 : d ^ 3;
}

struct pos {int y, x, d;};

bool used(int y, int x, const vector<map<int, bool>>& Rs) {
	return Rs[y].find(x) != Rs[y].end();
}

pos trace(const vector<map<int, bool>>& Rs, const vector<map<int, bool>>& Cs, vector<seg>& H, vector<seg>& V, int yf, int xf, pos p) {
	auto& [y, x, d] = p;
	bool done = false;
	while (!done) {
		//cerr << "at " << y << ' ' << x << ' ' << d << endl;
		switch (d) {
		case 0: {
			auto& row = Rs[y];
			auto nx = row.upper_bound(x);
			done = nx == row.end();
			int x2 = done ? xf : nx->first;
			seg cur{x, x2, y};
			if (used(y, x, Rs))
				cur.l++;
			if (!done)
				cur.r--;
			if (cur.l <= cur.r)
				H.push_back(cur);
			x = x2;
			if (!done)
				mirr(d, nx->second);
			break;
		}
		case 1: {
			auto& col = Cs[x];
			auto nx = col.upper_bound(y);
			done = nx == col.end();
			int y2 = done ? yf : nx->first;
			seg cur{y, y2, x};
			if (used(y, x, Rs))
				cur.l++;
			if (!done)
				cur.r--;
			if (cur.l <= cur.r)
				V.push_back(cur);
			y = y2;
			if (!done)
				mirr(d, nx->second);
			break;
		}
		case 2: {
			auto& row = Rs[y];
			auto nx = row.lower_bound(x);
			done = nx == row.begin();
			if (!done)
				--nx;
			int x2 = done ? 0 : nx->first;
			seg cur{x2, x, y};
			if (!done)
				cur.l++;
			if (used(y, x, Rs))
				cur.r--;
			if (cur.l <= cur.r)
				H.push_back(cur);
			x = x2;
			if (!done)
				mirr(d, nx->second);
			break;
		}
		case 3: {
			auto& col = Cs[x];
			auto nx = col.lower_bound(y);
			done = nx == col.begin();
			if (!done)
				--nx;
			int y2 = done ? 0 : nx->first;
			seg cur{y2, y, x};
			if (!done)
				cur.l++;
			if (used(y, x, Rs))
				cur.r--;
			if (cur.l <= cur.r)
				V.push_back(cur);
			y = y2;
			if (!done)
				mirr(d, nx->second);
			break;
		}
		}
	}
	sort(H.begin(), H.end());
	sort(V.begin(), V.end());
	return p;
}

const auto P1 = [](int x) {return x + 1;};
const auto M1 = [](int x) {return x - 1;};

int64_t ctIsects(const vector<seg>& H, const vector<seg>& V, int yf, int xf, int& rr, int& cc) {
	//sort(V.begin(), V.end(), [](const seg& l, const seg& r))
	int64_t ans = 0;
	PTree ST;
	int n = yf + 1, m = xf + 2;
	rup2(m);
	vector<int> R(n + 1);
	R[0] = ST.mkTree(vector<int>(m, 0));
	//cerr << "R0 " << R[0] << endl;
	for (int i = 0, j = 0; i < n; i++) {
		R[i + 1] = R[i];
		while (j < H.size() && H[j].y == i) {
			auto [l, r, y] = H[j++];
			R[i + 1] = ST.update(R[i + 1], P1, l, m);
			R[i + 1] = ST.update(R[i + 1], M1, r + 1, m);
		}
	}
	for (auto [t, b, x] : V) {
		int64_t cur = ST.query(R[b + 1], 0, x + 1, m) - ST.query(R[t], 0, x + 1, m);
		if (rr == -1 && cur != 0) {
			for (auto [l, r, y] : H)
				if (t <= y && y <= b && l <= x && x <= r && (rr == -1 || x < cc)) {
					rr = y;
					cc = x;
				    //cerr << t << ' ' << b << ' ' << x << ' ' << l << ' ' << r << ' ' << y << ' ' << rr << ' ' << cc << endl;
				}
		}
		ans += cur;
	}
	return ans;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	int t = 1;
	int R, C, M, N;
	while (cin >> R >> C >> M >> N) {
		//cerr << "Case " << t << endl;
		cout << "Case " << t++ << ": ";
		vector<pair<int, int>> A(M), B(N);
		unordered_map<int, int> YCC, XCC, IYCC, IXCC;
		{
			vector<int> Y{0, 1, R, R + 1}, X{0, 1, C, C + 1};
			for (auto& [y, x] : A) {
				cin >> y >> x;
				Y.push_back(y);
				X.push_back(x);
			}
			for (auto& [y, x] : B) {
				cin >> y >> x;
				Y.push_back(y);
				X.push_back(x);
			}
			sort(Y.begin(), Y.end());
			sort(X.begin(), X.end());
			for (int y : Y) {
				YCC.emplace(y, YCC.size());
				IYCC[YCC[y]] = y;
			}
			for (int x : X) {
				XCC.emplace(x, XCC.size());
				IXCC[XCC[x]] = x;
			}
		}
		//int rc = YCC.size(), cc = XCC.size();
		for (auto& [y, x] : A) {
			y = YCC[y];
			x = XCC[x];
		}
		for (auto& [y, x] : B) {
			y = YCC[y];
			x = XCC[x];
		}
		int yf = YCC[R + 1], xf = XCC[C + 1];
		vector<map<int, bool>> Rs(YCC.size()), Cs(XCC.size());
		for (auto [y, x] : A) {
			Rs[y].emplace(x, false);
			Cs[x].emplace(y, false);
		}
		for (auto [y, x] : B) {
			Rs[y].emplace(x, true);
			Cs[x].emplace(y, true);
		}
		vector<seg> AH, AV, BH, BV;
		auto [y1, x1, d1] = trace(Rs, Cs, AH, AV, yf, xf, {1, 0, 0});
		//cerr << "Ended at " << y1 << ' ' << x1 << ' ' << d1 << endl;
		/*cerr << "AH" << endl;
		for (seg s : AH)
			cerr << s.l << ' ' << s.r << ' ' << s.y << endl;
		cerr << "AV" << endl;
		for (seg s : AV)
			cerr << s.l << ' ' << s.r << ' ' << s.y << endl;*/
		if (y1 == yf - 1 && x1 == xf) {
			cout << 0 << endl;
			continue;
		}
		trace(Rs, Cs, BH, BV, yf, xf, {yf - 1, xf, 2});
		/*cerr << "BH" << endl;
		for (seg s : BH)
			cerr << s.l << ' ' << s.r << ' ' << s.y << endl;
		cerr << "BV" << endl;
		for (seg s : BV)
			cerr << s.l << ' ' << s.r << ' ' << s.y << endl;*/

		int rr1 = -1, cc1 = -1, rr2 = -1, cc2 = -1;
		int64_t k = ctIsects(AV, BH, xf, yf, cc1, rr1) + ctIsects(BV, AH, xf, yf, cc2, rr2);
		if (k == 0)
			cout << "impossible" << endl;
		else {
            if (rr2 != -1 && (rr1 == -1 || rr2 < rr1 || rr2 == rr1 && cc2 < cc1))
                tie(rr1, cc1) = make_pair(rr2, cc2);
            //cerr << rr1 << ' ' << cc1 << endl;
			cout << k << ' ' << IYCC[rr1] << ' ' << IXCC[cc1] << endl;
		}
	}
}
