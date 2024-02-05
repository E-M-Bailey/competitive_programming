#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, R, T;
	dso(int n) : P(n), R(n, 0), T(n)
	{
		iota(begin(P), end(P), 0);
		iota(begin(T), end(T), 0);
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
		T[y] = T[x];
		if (R[x] < R[y])
			swap(x, y);
		R[x] += R[x] == R[y];
		P[y] = x;
		return true;
	}
};

vector<vector<long long>>	   DP;
vector<bool>				   del;
vector<vector<pair<int, int>>> G;
vector<pair<int, int>>		   par;
long long					   krusk = 0, ans;
vector<int>					   depp;

void dfs(int u, int v)
{
	for (auto [w, wt] : G[v])
	{
		if (w == u)
			continue;
		par[w]	= {v, wt};
		depp[w] = depp[v] + 1;
		dfs(v, w);
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	DP.resize(n);
	G.resize(n);
	depp.resize(n);
	par.resize(n);
	vector<tuple<int, int, int>> E(m);
	for (auto &[d, a, b] : E)
	{
		cin >> a >> b >> d;
		a--;
		b--;
	}
	sort(begin(E), end(E));
	dso D(n);
	for (int i = 0; i < m; i++)
	{
		auto [d, a, b] = E[i];
		if (D.onion(a, b))
		{
			G[a].emplace_back(b, d);
			G[b].emplace_back(a, d);
			krusk += d;
		}
		else
		{
			DP[a].push_back(((long long)d << 32) | i);
			DP[b].push_back(((long long)d << 32) | i);
		}
	}
	ans = krusk;
	dfs(0, 0);
	par[0] = {-1, 0};

	dso d2(n);

	for (int i = 0; i < m; i++)
	{
		auto [d, a, b] = E[i];
		int mn		   = INT_MAX;
		if (par[a].first == b || par[b].first == a)
			continue;
		a = d2.T[d2.find(a)];
		b = d2.T[d2.find(b)];
		while (a != b)
		{
			if (depp[a] < depp[b])
				swap(a, b);
			mn = min(mn, par[a].second);
			d2.onion(par[a].first, a);
			a = d2.T[d2.find(a)];
		}
		ans = max(ans, krusk - mn + d);
	}

	cout << ans << '\n';
}
