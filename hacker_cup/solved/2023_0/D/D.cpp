#include <bits/stdc++.h>

using namespace std;




// Find bridges using DFS lowpoint
int dfs1(vector<vector<int>> const &G, vector<vector<int>> &B, vector<int> &num, int u, int v, int &t)
{
	int low_v = num[v] = t++, low_w;
	for (int w : G[v])
		if (w == u) // skip the parent
			continue;
		else if (num[w] == -1) // unvisited
		{
			low_v = min(low_v, low_w = dfs1(G, B, num, v, w, t));
			if (low_w > num[v]) // bridge
			{
				B[v].push_back(w);
				B[w].push_back(v);
			}
		}
		else // back-edge
			low_v = min(low_v, num[w]);
	return low_v;
}

// Find 2-edge-connected components
void dfs2(vector<vector<int>> const &G, vector<vector<int>> const &B, vector<int> &CI, vector<vector<int>> &CC, int v)
{
	CC.back().push_back(v);
	CI[v] = (int)CC.size() - 1;
	for (int w : G[v])
		if (!binary_search(begin(B[v]), end(B[v]), w) && CI[w] < 0) // skip visited vertices and bridges
			dfs2(G, B, CI, CC, w);
}

// Check if this 2-edge-connected component is bipartite
bool dfs3(vector<vector<int>> const &G, vector<int> const &CC, vector<int> &C, int v)
{
	for (int w : G[v])
	{
		if (!binary_search(begin(CC), end(CC), w))
			continue;
		else if (C[w] < 0)
		{
			C[w] = !C[v];
			if (!dfs3(G, CC, C, w))
				return false;
		}
		else if (C[w] == C[v])
			return false;
	}
	return true;
}

// Distance to non-bipartie block in bridge-block tree using all-roots DFS (pass 1)
void dfs4(vector<vector<int>> &T, vector<int> &D, int v)
{
	for (int w : T[v])
	{
		T[w].erase(find(begin(T[w]), end(T[w]), v));
		dfs4(T, D, w);
		D[v] = min(D[v], D[w] + 1);
	}
}

// Distance to non-bipartie block in bridge-block tree using all-roots DFS (pass 2)
void dfs5(vector<vector<int>> const &T, vector<int> &D, int v)
{
	for (int w : T[v])
	{
		D[w] = min(D[w], D[v] + 1);
		dfs5(T, D, w);
	}
}

// Build binary lifting structure which stores path mins over D (computed in the last two DFS passes)
void dfs6(vector<vector<int>> const &T, vector<int> const &D, vector<vector<pair<int, int>>> &P, int v)
{
	for (int w : T[v])
	{
		P[w].emplace_back(v, min(D[w], D[v]));
		while (P[P[w].back().first].size() >= P[w].size())
		{
			auto [u, d] = P[P[w].back().first][P[w].size() - 1];
			P[w].emplace_back(u, min(d, P[w].back().second));
		}
		dfs6(T, D, P, w);
	}
}

// Depth
void dfs7(vector<vector<int>> const &T, vector<int> &L, int v)
{
	for (int w : T[v])
	{
		L[w] = L[v] + 1;
		dfs7(T, L, w);
	}
}

int query(int u, int v, vector<vector<pair<int, int>>> const &P, vector<int> const &D, vector<int> const &L)
{
	int ans = min(D[u], D[v]), cur;
	while (L[u] > L[v])
	{
		int i = __builtin_ctz(L[u] - L[v]);
		tie(u, cur) = P[u][i];
		ans = min(ans, cur);
	}
	while (L[u] < L[v])
	{
		int i = __builtin_ctz(L[v] - L[u]);
		tie(v, cur) = P[v][i];
		ans = min(ans, cur);
	}
	int i = (int)P[u].size() - 1;
	while (u != v)
	{
		while (i > 0 && (i >= (int)P[u].size() || P[u][i].first == P[v][i].first))
			i--;
		tie(u, cur) = P[u][i];
		ans = min(ans, cur);
		tie(v, cur) = P[v][i];
		ans = min(ans, cur);
	}
	return ans;
}

int main()
{
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++)
	{
		cout << "Case #" << tt << ": ";
		int n, m;
		cin >> n >> m;

		vector<vector<int>> G(n);
		for (int i = 0; i < m; i++)
		{
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			G[a].push_back(b);
			G[b].push_back(a);
		}

		vector<vector<int>> B(n);
		{ // find bridges
			vector<int> num(n, -1);
			int T = 0;
			for (int v = 0; v < n; v++)
				if (num[v] == -1)
					dfs1(G, B, num, v, v, T);
			for (auto &BB : B)
				sort(begin(BB), end(BB));
		}

		vector<vector<int>> CC;
		vector<int> CI(n, -1);

		// find 2-edge-connected components
		for (int v = 0; v < n; v++)
			if (CI[v] < 0)
			{
				CC.emplace_back();
				dfs2(G, B, CI, CC, v);
				sort(begin(CC.back()), end(CC.back()));
			}

		int k = (int)CC.size();
		vector<int> C(n, -1);
		vector<bool> BP(k);
		// find bipartite components
		for (int i = 0; i < k; i++)
		{
			int v = CC[i][0];
			C[v] = 0;
			BP[i] = dfs3(G, CC[i], C, v);
		}

		if (all_of(begin(BP), end(BP), identity{}))
		{
			int q;
			cin >> q;
			cout << -q << '\n';
			int a;
			for (int i = 0; i < q * 2; i++)
				cin >> a;
			continue;
		}

		// Distances to non-bipartite components using all-roots
		vector<vector<int>> T(k);
		for (int v = 0; v < n; v++)
			for (int w : B[v])
				T[CI[v]].push_back(CI[w]);
		vector<int> D(k);
		for (int i = 0; i < k; i++)
			D[i] = BP[i] ? INT_MAX / 2 : 0;

		dfs4(T, D, 0);
		dfs5(T, D, 0);

		// Binary lifting
		vector<vector<pair<int, int>>> P(k);
		dfs6(T, D, P, 0);

		vector<int> L(k);
		dfs7(T, L, 0);

		int q;
		cin >> q;
		int64_t ans = 0;
		while (q--)
		{
			int a, b;
			cin >> a >> b;
			a--;
			b--;
			ans += query(CI[a], CI[b], P, D, L);
		}
		cout << ans << '\n';
	}
}
