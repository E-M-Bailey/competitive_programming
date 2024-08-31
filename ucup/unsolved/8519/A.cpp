#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> R, P;
	int			k;
	dso(int n) : R(n), P(n), k(n)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = pair{P[x], P[P[x]]};
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
		R[x] += x == y;
		k--;
		return true;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> E(m);
	for (auto &[u, v] : E)
	{
		cin >> u >> v;
		u--;
		v--;
	}
	E.emplace_back(0, n - 1);
	m++;

	vector<vector<int>> G1(n), Gn(n);
	for (int i = 0; i < m; i++)
	{
		auto [u, v] = E[i];
		G1[u].push_back(i);
		Gn[v].push_back(i);
	}
	vector<bool> R1(n, false), Rn(n, false);
	R1[0]	  = true;
	Rn[n - 1] = true;
	for (int u = 0; u < n; u++)
	{
		if (!R1[u])
			continue;
		for (int i : G1[u])
		{
			R1[E[i].second] = true;
		}
	}
	for (int u = n; u--;)
	{
		if (!Rn[u])
			continue;
		for (int i : Gn[u])
		{
			Rn[E[i].first] = true;
		}
	}

	int e = 0;

	dso D(n);
	for (int i = 0; i < m; i++)
	{
		auto [u, v] = E[i];
		if (R1[u] && Rn[v])
		{
			e++;
			D.onion(u, v);
		}
	}

	cout << e - n + D.k;
}