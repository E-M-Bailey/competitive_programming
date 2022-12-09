#include <bits/stdc++.h>
using namespace std;

#define sz(c) int(c.size())
#define all(c) (c).begin(), (c).end()
#define rall(c) (c).rbegin(), (c).rend()
#define rep(i, lo, hi) for (int i = (lo); i < (hi); i++)
#define rrep(i, lo, hi) for (int i = (hi - 1); i >= (lo); i--)

typedef long double T;
const T EPS = 1e-8;
const T PI = 4 * atan((T)1);
const T INF = numeric_limits<T>::infinity();
typedef array<T, 3> V;

V operator-(V l) {rep(i, 0, 3) l[i] = -l[i]; return l;}
V& operator+=(V& l, const V& r) {rep(i, 0, 3) l[i] += r[i]; return l;}
V& operator-=(V& l, const V& r) {rep(i, 0, 3) l[i] -= r[i]; return l;}
V& operator*=(V& l, const V& r) {rep(i, 0, 3) l[i] *= r[i]; return l;}
V& operator*=(V& l, T r) {rep(i, 0, 3) l[i] *= r; return l;}
V& operator/=(V& l, const V& r) {rep(i, 0, 3) l[i] /= r[i]; return l;}
V& operator/=(V& l, T r) {rep(i, 0, 3) l[i] /= r; return l;}
V operator+(V l, const V& r) {return l += r;}
V operator-(V l, const V& r) {return l -= r;}
V operator*(V l, const V& r) {return l *= r;}
V operator*(V l, T r) {return l *= r;}
V operator*(T l, V r) {return r *= l;}
V operator/(V l, const V& r) {return l /= r;}
V operator/(V l, T r) {return l /= r;}
T sum(const V& l) {return accumulate(all(l), (T)0);}
T dot(const V& l, const V& r) {return sum(l * r);}
T norm2(const V& l) {return dot(l, l);}
T norm(const V& l) {return sqrt(norm2(l));}
T dist2(const V& l, const V& r) {return norm2(r - l);}
T dist(const V& l, const V& r) {return norm(r - l);}
T sq(T l) {return l * l;}
T cross(T a, T b, T c, T d) {return a * d - b * c;}
V cross(V l, V r) {return {cross(l[1], l[2], r[1], r[2]), -cross(l[0], l[2], r[0], r[2]), cross(l[0], l[1], r[0], r[1])};}

const V ZERO{0, 0, 0};
ostream& operator<<(ostream& strm, const V& v) {
	return strm << '(' << v[0] << ", " << v[1] << ", " << v[2] << ')';
}

struct Sphere2 {
	V c;
	T r2;
};
ostream& operator<<(ostream& strm, const Sphere2& s) {
	return strm << '[' << s.c << ' ' << s.r2 << ']';
}

const Sphere2 NIL2{ZERO, -1};

struct Sphere1 {
	V c;
	T r2;
	V a;
};
ostream& operator<<(ostream& strm, const Sphere1& s) {
	return strm << '[' << s.c << ' ' << s.r2 << ' ' << s.a << ']';
}

const Sphere1 NIL1{ZERO, -1, ZERO};

struct Sphere0 {
	V c;
	T r2;
	V a, b;
};
ostream& operator<<(ostream& strm, const Sphere0& s) {
	return strm << '[' << s.c << ' ' << s.r2 << ' ' << s.a << ' ' << s.b << ']';
}

const Sphere0 NIL0{ZERO, -1, ZERO, ZERO};

Sphere1 isect22(const Sphere2& s1, const Sphere2& s2) {
	if (s1.r2 < -EPS || s2.r2 < -EPS) return NIL1;
	V a = s2.c - s1.c;
	a /= norm(a);
	T x1 = dot(s1.c, a), x2 = dot(s2.c, a), dx = x2 - x1;
	T x = (T)0.5 * (sq(x2) - sq(x1) - s2.r2 + s1.r2) / dx;
	//cerr << x << endl;
	T r2 = s1.r2 - sq(x - x1);
	if (r2 < -EPS) return NIL1;
	V c = s1.c + a * (x - x1);
	return {c, r2, a};
}

Sphere0 isect12(const Sphere1& s1, const Sphere2& s2) {
	if (s1.r2 < -EPS || s2.r2 < -EPS) return NIL0;
	V a = s1.a;
	//cerr << a << endl;
	T y1 = dot(a, s1.c), y2 = dot(a, s2.c), dy = y2 - y1;
	V c2 = s2.c - a * dy;
	T r22 = s2.r2 - sq(dy);
	V b = c2 - s1.c;
	b /= norm(b);
	T x1 = dot(s1.c, b), x2 = dot(c2, b), dx = x2 - x1;
	T x = (T)0.5 * (sq(x2) - sq(x1) - r22 + s1.r2) / dx;
	T r2 = s1.r2 - sq(x - x1);
	if (r2 < -EPS) return NIL0;
	V c = s1.c + b * (x - x1);
	return {c, r2, a, b};
}

Sphere0 isect222(const Sphere2& s1, const Sphere2& s2, const Sphere2& s3) {
	return isect12(isect22(s1, s2), s3);
}

Sphere1 great(const Sphere2& s, const V& a, const V& b) {
	V ca = a - s.c, cb = b - s.c;
	V axis = cross(ca, cb);
	axis /= norm(axis);
	return {s.c, s.r2, axis};
}

vector<V> getPts(const Sphere0& s) {
	if (s.r2 < -EPS) return {};
	else if (s.r2 <= EPS) return {s.c};
	V v = cross(s.a, s.b);
	v *= sqrt(s.r2) / norm(v);
	return {s.c - v, s.c + v};
}

// zero, v should be on s.
T angle(const Sphere1& s, const V& zero, const V& v) {
	V x = zero - s.c, y = v - s.c;
	T cp = dot(s.a, cross(x, y) / s.r2);
	T dp = dot(x, y);
	T ans = asin(cp);
	if (ans < 0) ans += 2 * PI;
	if (dp < 0) ans = (ans > PI ? 3 : 1) * PI - ans;
	return ans;
}

bool checkPath(T s, T t, const vector<pair<T, T>>& I) {
	//cerr << s << ' ' << t << endl;
	for (auto [lo, hi] : I) {
		if (lo <= s + EPS)
			s = max(s, hi);
	}
	return s + EPS >= t;
}

const T R = 6370;
const Sphere2 EARTH{ZERO, sq(R)};

T sDist(T cDist) {
	return 2 * R * asin(cDist / (2 * R));
}
T cDist(T sDist) {
	return 2 * R * sin(sDist / (2 * R));
}
V sp2Cart(T r, T phi, T theta) {
	T sp = sin(phi), cp = cos(phi), st = sin(theta), ct = cos(theta);
	return {r * cp * ct, r * sp * ct, r * st};
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}

	int tc = 0;
	int n;
	T sc;
	while (cin >> n >> sc) {
		cout << "Case " << ++tc << ":" << endl;
		//cerr << "Case " << tc << ": ";
		T r = cDist(sc), r2 = r * r;
		vector<Sphere2> S(n);
		for (Sphere2& sp : S) {
			T phi, theta;
			cin >> phi >> theta;
			phi *= PI / 180;
			theta *= PI / 180;
			sp = {sp2Cart(R, phi, theta), r2};
		}
		vector<pair<V, int>> P;
		vector<int> Pidx(n);
		rep(i, 0, n) {
			Pidx[i] = P.size();
			P.emplace_back(S[i].c, i);
			for (int j = i + 1; j < n; j++) {
				//cerr << isect22(EARTH, S[i]) << ' ' << isect12(isect22(EARTH, S[i]), S[j]) << endl;
				//cerr << isect22(EARTH, S[i])
				for (V p : getPts(isect222(EARTH, S[i], S[j])))
					P.emplace_back(p, -1);
			}
		}
		int m = P.size();
		/*
		cerr << "S:" << endl;
		rep(i, 0, n)
		cerr << ' ' << i << ' ' << S[i] << endl;
		cerr << "Pidx:" << endl;
		for (int i = 0; i < n; i++)
			cerr << ' ' << i << ' ' << Pidx[i] << endl;
		cerr << "P:" << endl;
		for (int i = 0; i < m; i++)
			cerr << ' ' << i << ' ' << P[i].first << ' ' << P[i].second << endl;
			*/
		vector<vector<pair<int, T>>> G(m);
		rep(i, 0, m) rep(j, i + 1, m) {
			Sphere1 gc = great(EARTH, P[i].first, P[j].first);
			vector<pair<T, T>> I;
			for (const Sphere2& s : S) {
				vector<V> pts = getPts(isect12(gc, s));
				if (pts.size() < 2) continue;
				T a = angle(gc, P[i].first, pts[0]);
				T b = angle(gc, P[i].first, pts[1]);
				if (a > b) swap(a, b);
				if (b > a + PI) {
					swap(a, b);
					b += 2 * PI;
					I.emplace_back(a - 2 * PI, b - 2 * PI);
				}
				I.emplace_back(a, b);
			}
			//cerr << i << ' ' << j << ' ' << gc << ' '  << P[i].first << ' ' << P[j].first << endl;
			T a1 = angle(gc, P[i].first, P[j].first);
			sort(all(I));
			//cerr << I.size() << endl;
			bool p1 = checkPath(0, a1, I), p2 = checkPath(a1, 2 * PI, I);
			//cerr << "Paths checked" << endl;
			if (!(p1 || p2)) continue;
			T d1 = p1 ? a1 * R : INF;
			T d2 = p2 ? (2 * PI - a1) * R : INF;
			T d = min(d1, d2);
			G[i].emplace_back(j, d);
			G[j].emplace_back(i, d);
		}

		vector<vector<T>> D(n, vector<T>(n));
		vector<bool> V(m);
		priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> PQ;
		{
			vector<vector<T>> D2(n, vector<T>(m, INF));
			rep(i, 0, n) {
				int s = Pidx[i];
				auto& DD = D2[i];
				fill(all(V), false);
				PQ.emplace(0, s);
				while (!PQ.empty()) {
					auto [d, v] = PQ.top();
					PQ.pop();
					if (V[v]) continue;
					V[v] = true;
					DD[v] = d;
					for (auto [w, wt] : G[v])
						if (!V[w])
							PQ.emplace(d + wt, w);
				}
			}
			rep(i, 0, n) rep(j, 0, n) D[i][j] = D2[i][Pidx[j]];
		}


		int q;
		cin >> q;
		V.resize(n);
		while (q--) {
			int s, t;
			T c;
			cin >> s >> t >> c;
			s--;
			t--;
			vector<vector<T>> D2 = D;
			fill(all(V), false);
			for (auto& DD : D2)
				for (T& d : DD)
					if (d > c + EPS)
						d = INF;
			PQ.emplace(0, s);
			while (!PQ.empty()) {
				auto [d, v] = PQ.top();
				PQ.pop();
				if (V[v])
					continue;
				V[v] = true;
				if (v == t) {
					if (isfinite(d))
						cout << fixed << setprecision(3) << d << endl;
					else
						cout << "impossible" << endl;
					while (!PQ.empty())
						PQ.pop();
					break;
				}
				rep(w, 0, n) if(!V[w])
					PQ.emplace(d + D2[v][w], w);
			}
		}
	}
}
