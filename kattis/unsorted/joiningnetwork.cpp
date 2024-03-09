#include <bits/stdc++.h>

using namespace std;

typedef __int128_t T;

ostream &operator<<(ostream &os, __int128_t x)
{
	if (x == 0)
		return os << '0';
	static char buf[39]{};
	char *ptr = buf + 38;
	bool neg = x < 0;
	while (x)
	{
		*--ptr = char(abs(x % 10) + '0');
		x /= 10;
	}
	if (neg)
		*--ptr = '-';
	return os << ptr;
}

struct tree
{
	T n;
	vector<vector<int>> G;
	vector<T> S0, S1, S2;
	vector<tuple<T, T, int>> hull;

	void dfs1(int u, int v)
	{
		for (int w : G[v])
			if (w != u)
			{
				dfs1(v, w);
				S0[v] += S0[w];
				S1[v] += S1[w];
				S2[v] += S2[w];
			}
		S2[v] += 2 * S1[v] + S0[v];
		S1[v] += S0[v];
		S0[v] += 1;
	}

	T s0, s1, s2;

	void dfs2(int u, int v)
	{
		S2[v] += s2;
		S1[v] += s1;
		S0[v] += s0;
		for (int w : G[v])
			if (w != u)
			{
				s2 = S2[v] - (S2[w] + 2 * S1[w] + S0[w]);
				s1 = S1[v] - (S1[w] + S0[w]);
				s0 = S0[v] - S0[w];
				s2 += 2 * s1 + s0;
				s1 += s0;
				dfs2(v, w);
			}
	}

	T internal()
	{
		return accumulate(begin(S2), end(S2), (T)0) / 2;
	}

	T opt(T a, T b)
	{
		int lo = 0, hi = (int)hull.size() - 1;
		while (lo < hi)
		{
			int mid = (lo + hi) / 2;
			auto [x1, y1, i] = hull[mid];
			if (mid + 1 == (int)hull.size())
				cerr << "help!" << endl;
			auto [x2, y2, j] = hull[mid + 1];
			auto dx = x2 - x1, dy = y2 - y1;
			if (dy * a >= b * dx)
				hi = mid;
			else
				lo = mid + 1;
		}
		auto [x, y, i] = hull[lo];
		//cerr << "opt: " << x << ' ' << y << ' ' << i << ' ' << a * x + b * y << endl;

		return a * x + b * y;
	}

	tree()
	{
		int N;
		cin >> N;
		n = N;
		G.resize(N);
		for (int i = 0; i < N - 1; i++)
		{
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		S0.resize(N);
		S1.resize(N);
		S2.resize(N);
		dfs1(0, 0);
		//for (T i = 0; i < n; i++)
		//	cerr << i << ' ' << S0[i] << ' ' << S1[i] << ' ' << S2[i] << endl;
		s0 = s1 = s2 = 0;
		dfs2(0, 0);

		//for (int i = 0; i < n; i++)
		//	cerr << i << ' ' << S0[i] << ' ' << S1[i] << ' ' << S2[i] << endl;
		//cerr << endl;

		vector<tuple<T, T, int>> pts;
		for (int i = 0; i < N; i++)
			pts.emplace_back(2 * S1[i], S2[i] + 2 * S1[i], i);
		sort(begin(pts), end(pts));
		int ct = 1;
		while (ct < N && get<0>(pts[ct]) == get<0>(pts[0]))
			ct++;
		reverse(begin(pts), begin(pts) + ct);
		pts.erase(unique(begin(pts), end(pts), [](const tuple<T, T, int> &a, const tuple<T, T, int> &b)
			{
				//cerr << ' ' << get<0>(a) << ' ' << get<0>(b) << endl;
				return get<0>(a) == get<0>(b) && get<1>(a) == get<1>(b);
			}), end(pts));
		int m = (int)pts.size();
		//for (auto [x, y, idx] : pts)
		//	cerr << "point " << x << ' ' << y << ' ' << idx << endl;
		for (int i = 0; i < m; i++)
		{
			auto [x, y, idx] = pts[i];
			while (hull.size() >= 2)
			{
				auto [xa, ya, j1] = hull[hull.size() - 1];
				auto [xb, yb, j2] = hull[hull.size() - 2];
				T a = xb - xa, b = yb - ya, c = x - xa, d = y - ya;
				T det = a * d - b * c;
				if (det <= 0)
					hull.pop_back();
				else
					break;
			}
			hull.emplace_back(x, y, idx);
		}
		//cerr << "hull:\n";
		//for (auto [x, y, i] : hull)
		//	cerr << ' ' << i << ' ' << x << ' ' << y << endl;
		//cerr << endl;
	}


};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	tree A, B;

	T best = numeric_limits<T>::max() / 2;
	for (int i = 0; i < (int)B.n; i++)
	{
		//cerr << i << ' ' << A.n * (B.S2[i] + 2 * B.S1[i]) << endl;
		best = min(best, A.opt(B.S1[i], B.n) + A.n * (B.S2[i] + 2 * B.S1[i]));
	}
	T ans = best + A.n * B.n + A.internal() + B.internal();
	cout << ans;
	//cout << best + (T)A.n * B.n + A.internal() + B.internal();
}