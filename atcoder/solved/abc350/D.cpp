#include <bits/stdc++.h>

using namespace std;

int dfs(int v, vector<vector<int>> const &G, vector<bool> &vis)
{
	int ans = 1;
	vis[v]	= true;
	for (int w : G[v])
	{
		if (vis[w])
			continue;
		ans += dfs(w, G, vis);
	}
	return ans;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<bool>		vis(n);
	vector<vector<int>> G(n);
	long long			ans = -m;
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for (int i = 0; i < n; i++)
		if (!vis[i])
		{
			long long cur = dfs(i, G, vis);
			ans += cur * (cur - 1) / 2;
		}
	cout << ans;
}
