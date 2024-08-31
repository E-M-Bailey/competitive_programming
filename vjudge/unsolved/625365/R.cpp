#include <bits/stdc++.h>

using namespace std;

struct dso
{
	int			n, k;
	vector<int> P, R;
	dso(int N) : n(N), k(N), P(N), R(N)
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
		if ((x = find(x)) == (y = find(y)))
			return false;
		k--;
		if (R[x] < R[y])
			swap(x, y);
		R[x] += R[x] == R[y];
		P[y] = x;
		return true;
	}
};

void dfs(int v, vector<int> &H, vector<vector<pair<int, int>>> &G, vector<vector<pair<int, int>>> &P)
{
	for (auto [w, c] : G[v])
	{
		H[w] = H[v] + 1;
		G[w].erase(find(begin(G[w]), end(G[w]), pair{v, c}));
		P[w].emplace_back(v, c);
		for (int i = 0; i < (int)size(P[P[w][i].first]); i++)
			P[w].emplace_back(P[P[w][i].first][i].first, max(P[w][i].second, P[P[w][i].first][i].second));
		dfs(w, H, G, P);
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m, d;
	cin >> n >> m >> d;
	vector<tuple<int, int, int>> E;
	for (int i = 0; i < m; i++)
	{
		int u, v, c;
		cin >> u >> v >> c;
		u--;
		v--;
		c = 2 * c + (i >= n - 1);
		E.emplace_back(c, u, v);
	}
	sort(begin(E), end(E));

	int		  dinit = 0;
	long long cbest = 1;

	vector<vector<pair<int, int>>> G(n), P(n);
	vector<int>					   H(n);
	dso							   D(n);
	for (auto [c, u, v] : E)
		if (D.onion(u, v))
		{
			G[u].emplace_back(v, c);
			G[v].emplace_back(u, c);
			dinit += c % 2;
			cbest = max(cbest, 3ll * min(c / 2, d) + 1);
		}

	dfs(0, H, G, P);

	for (auto [c, u, v] : E)
	{
		c -= 2 * min(c / 2, d);
		int c2 = 0;
		if (H[u] < H[v])
			swap(u, v);
		int dh = H[u] - H[v];
		for (int i = 0; i < 20; i++)
			if (dh & (1 << i))
			{
				c2 = max(c2, P[u][i].second);
				u  = P[u][i].first;
			}
		int l = 20;
		while (u != v)
		{
			while (l > 0 && (l >= (int)size(P[u]) || P[u][l].first == P[v][l].first))
				l--;
			c2 = max(c2, P[u][l].second);
			u  = P[u][l].first;
			c2 = max(c2, P[v][l].second);
			v  = P[v][l].first;
		}
		if (c2 > c)
			cbest = max(cbest, (c2 / 2 - c / 2) * 3ll + 1 + c2 % 2 - c % 2);
	}

	cout << dinit - cbest % 3 + 1;
}
