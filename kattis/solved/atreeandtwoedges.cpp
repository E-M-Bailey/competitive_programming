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
			tie(x, P[x]) = pair{P[x], P[P[x]]};
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x), y = find(y);
		if (x == y)
			return false;
		if (R[x] < R[y])
			swap(x, y);
		P[y] = x;
		R[x] += R[x] == R[y];
		return true;
	}
};

vector<vector<int>> G;
vector<vector<int>> P;
vector<int> L;
void dfs(int v)
{
	for (int w : G[v])
	{
		L[w] = L[v] + 1;
		auto it = find(begin(G[w]), end(G[w]), v);
		G[w].erase(it);
		P[w].push_back(v);
		for (int i = 0; i < (int)P[P[w][i]].size(); i++)
			P[w].push_back(P[P[w][i]][i]);
		dfs(w);
	}
}

int lca(int u, int v)
{
	if (L[u] < L[v])
		swap(u, v);
	while (L[u] > L[v])
		u = P[u][__builtin_ctz(L[u] - L[v])];

	int i = (int)P[u].size() - 1;
	while (u != v)
	{
		while (i > 0 && (i >= (int)P[u].size() || P[u][i] == P[v][i]))
			i--;
		u = P[u][i];
		v = P[v][i];
	}
	return u;
}
bool anc(int u, int v)
{
	while (L[u] > L[v])
		u = P[u][__builtin_ctz(L[u] - L[v])];
	return u == v;
}
bool betw(int u, int v, int w)
{
	return anc(v, u) && anc(u, w);
}
bool good(int u, int v, int w, int x)
{
	int a = lca(u, v), b = lca(w, x);
	return !betw(a, w, b) && !betw(a, x, b) && !betw(b, u, a) && !betw(b, v, a);
}
bool good(vector<int> V)
{
	for (int i = 0; i < (int)V.size(); i += 2)
		for (int j = i + 2; j < (int)V.size(); j += 2)
			if (!good(V[i], V[i + 1], V[j], V[j + 1]))
				return false;
	return true;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;
	G.resize(n);
	P.resize(n);
	L.resize(n);
	dso D(n);
	int w = -1, x = -1, y = -1, z = -1;
	for (int i = 0; i < n + 1; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		if (D.onion(a, b))
		{
			G[a].push_back(b);
			G[b].push_back(a);
		}
		else if (w < 0)
		{
			w = a;
			x = b;
		}
		else
		{
			y = a;
			z = b;
		}
	}
	dfs(0);

	while (q--)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		int ans = 1;
		ans += good({u, w, x, v});
		ans += good({u, y, z, v});
		ans += good({v, w, x, u});
		ans += good({v, y, z, u});
		ans += good({u, w, x, y, z, v});
		ans += good({u, x, w, y, z, v});
		ans += good({u, w, x, z, y, v});
		ans += good({u, x, w, z, y, v});
		ans += good({v, w, x, y, z, u});
		ans += good({v, x, w, y, z, u});
		ans += good({v, w, x, z, y, u});
		ans += good({v, x, w, z, y, u});
		cout << ans << '\n';
	}
}