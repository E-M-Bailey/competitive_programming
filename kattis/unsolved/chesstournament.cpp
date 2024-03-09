#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, R;
	dso(int n) : P(n), R(n)
	{
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

vector<bool> vis, ons;
vector<vector<int>> G;
bool dfs(int v)
{
	// cerr << "dfs " << v << ' ' << vis[v] << ' ' << ons[v] << endl;
	if (vis[v])
		return true;
	if (ons[v])
		return false;
	ons[v] = true;
	for (int w : G[v])
		if (!dfs(w))
			return false;
	ons[v] = false;
	vis[v] = true;
	return true;
}

int main()
{
	int m, n;
	cin >> n >> m;
	dso D(n);

	vector<pair<int, int>> E;
	while (m--)
	{
		int u, v;
		char c;
		cin >> u >> c >> v;
		// cerr << u << ' ' << v << endl;
		if (c == '=')
			D.onion(u, v);
		else
			E.emplace_back(u, v);
	}
	G.resize(n);
	for (auto [u, v] : E)
		G[D.find(u)].push_back(D.find(v));

	vis.resize(n);
	ons.resize(n);

	bool ans = true;
	for (int v = 0; v < n; v++)
		if (v == D.P[v])
			ans &= dfs(v);

	cout << (ans ? "consistent" : "inconsistent");
}