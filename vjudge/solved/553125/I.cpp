#include <bits/stdc++.h>

using namespace std;

typedef long double T;
const T E = 1e-7l;
const T INF = numeric_limits<T>::infinity();

vector<pair<T, T>> P;

int add(T x, T y)
{
	int id = (int)P.size();
	P.emplace_back(x, y);
	return id;
}

struct line
{
	T a, b, c, m, l, r;
	T t(T x, T y) const
	{
		return a * y - b * x;
	}
	line(T x1, T y1, T x2, T y2):
		a(y2 - y1),
		b(x1 - x2),
		c(a* x1 + b * y1),
		m(sqrtl(a* a + b * b)),
		l(t(x1, y1) - E),
		r(t(x2, y2) + E)
	{}
	bool on(T x, T y) const
	{
		if (abs(a * x + b * y - c) >= E)
			return false;
		T tim = t(x, y);
		return l < tim && tim < r;
	}
	friend int isect(const line& l, const line& r)
	{
		T a = l.a, b = l.b, c = r.a, d = r.b, e = l.c, f = r.c;
		T det = a * d - b * c;
		if (abs(det) < E)
			return -1;
		T x = (d * e - b * f) / det, y = (-c * e + a * f) / det;
		T tl = l.t(x, y);
		if (tl < l.l || tl > l.r)
			return -1;
		T tr = r.t(x, y);
		if (tr < r.l || tr > r.r)
			return -1;
		return add(x, y);
	}
};

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;
	vector<line> L;
	for (int i = 0; i < n; i++)
	{
		T x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		L.emplace_back(x1, y1, x2, y2);
	}
	vector<vector<int>> I(n);
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			int id = isect(L[i], L[j]);
			if (id < 0)
				continue;
			I[i].push_back(id);
			I[j].push_back(id);
		}

	T X, Y, V;
	cin >> X >> Y >> V;
	int s = add(X, Y);
	for (int i = 0; i < n; i++)
		if (L[i].on(X, Y))
			I[i].push_back(s);

	T x1, y1, x2, y2, v;
	cin >> x1 >> y1 >> x2 >> y2 >> v;
	line LF(x1, y1, x2, y2);

	vector<pair<int, T>> F;
	for (int i = 0; i < n; i++)
	{
		int id = isect(L[i], LF);
		if (id < 0)
			continue;
		I[i].push_back(id);
		auto [x, y] = P[id];
		T dx = x - x1, dy = y - y1;
		F.emplace_back(id, sqrtl(dx * dx + dy * dy) / v);
	}

	int N = (int)P.size();
	vector<vector<pair<int, T>>> G(N);
	for (int i = 0; i < n; i++)
	{
		sort(begin(I[i]), end(I[i]), [&](int a, int b)
			{
				auto [xa, ya] = P[a];
				auto [xb, yb] = P[b];
				return L[i].t(xa, ya) < L[i].t(xb, yb);
			});
		for (int j = 1; j < (int)I[i].size(); j++)
		{
			int a = I[i][j - 1], b = I[i][j];
			auto [xa, ya] = P[a];
			auto [xb, yb] = P[b];
			T d = (L[i].t(xb, yb) - L[i].t(xa, ya)) / L[i].m;
			G[a].emplace_back(b, d);
			G[b].emplace_back(a, d);
		}
	}

	vector<T> D(N, INF);
	vector<bool> vis(N);
	priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> Q;
	D[s] = 0;
	Q.emplace(0, s);
	while (!Q.empty())
	{
		auto [d, u] = Q.top();
		Q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (auto [w, wt] : G[u])
		{
			if (vis[w] || wt + d > D[w])
				continue;
			D[w] = wt + d;
			Q.emplace(wt + d, w);
		}
	}

	T ans = INF;
	for (auto [u, d] : F)
	{
		//cerr << P[u].first << ' ' << P[u].second << ' ' << D[u] / V << ' ' << d << endl;
		if (D[u] / V < d + E)
			ans = min(ans, d);
	}

	if (ans == INF)
		cout << "Impossible";
	else
		cout << fixed << setprecision(7) << ans;
}
