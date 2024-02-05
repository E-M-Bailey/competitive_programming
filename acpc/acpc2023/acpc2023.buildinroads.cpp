#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, R;
	dso(int n) : P(n), R(n)
	{
		iota(begin(P), end(P), 0);
	}
	void clear()
	{
		fill(begin(R), end(R), 0);
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = make_pair(P[x], P[P[x]]);
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (R[x] < R[y])
			swap(x, y);
		P[y] = x;
		R[x] += R[x] == R[y];
		return true;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	vector<tuple<long double, int64_t, int64_t, int64_t, int64_t>> E(m);
	long double lo = 0, hi = 0;
	for (auto &[x, u, v, p, g] : E)
	{
		cin >> u >> v >> p >> g;
		u--;
		v--;
		hi += p;
	}

	dso D(n);
	int64_t P = 0, G = 0;
	for (int i = 0; i < 100; i++)
	{
		D.clear();
		long double r = (lo + hi) / 2;
		for (auto &[x, u, v, p, g] : E)
			x = p - r * g;
		sort(begin(E), end(E));
		long double cur = 0;
		int64_t cp = 0, cg = 0;
		for (auto [x, u, v, p, g] : E)
			if (D.onion(u, v))
			{
				cur += x;
				cp += p;
				cg += g;
			}
		if (cur <= 0)
		{
			if (cp * G <= P * cg)
				tie(P, G) = make_pair(cp, cg);
			hi = r;
		}
		else
			lo = r;
	}
	auto g = __gcd(P, G);
	cout << P / g << '/' << G / g;
}