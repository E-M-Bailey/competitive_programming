#include <bits/stdc++.h>

using namespace std;

// adjacency lists, parent, vertex, DFS number counter, DFS numbers, DFS lowpoints, articulation points
int dfs(vector<vector<int>> const &adj, int u, int v, int &t, int &art, vector<int> &num)
{
	int low_v = num[v] = t++, low_w;
	for (int w : adj[v])
		if (w != u) // skip the parent
			if (num[w] == -1)
			{ // unvisited
				low_v = min(low_v, low_w = dfs(adj, v, w, t, art, num));
				art += v != 0 && low_w >= num[v]; // omit the root case for this problem
			}
			else
				low_v = min(low_v, num[w]); // visited, back-edge
	return low_v;
}
bool strong_enough(vector<vector<int>> const &adj)
{
	vector<int> num(adj.size(), -1);
	int			t = 0, art = 0; // art = # of non-root articulation points
	dfs(adj, 0, 0, t, art, num);
	return t == (int)adj.size() && art == 0; // connected, no non-root articulation points
}
int main()
{
	long long n, lo = 1, hi = 4e18, dx, dy;
	cin >> n;
	struct
	{
		int x, y;
	} P[n + 1]{}; // P[0] = (0, 0) is the rock
	for (int i = 1; i <= n; i++)
		cin >> P[i].x >> P[i].y;
	while (lo < hi)
	{ // binary search on the answer squared
		vector<vector<int>> adj(n + 1);
		for (int u = 0; u <= n; u++)
			for (int v = 0; v <= n; v++)
				if (dx = P[v].x - P[u].x, dy = P[v].y - P[u].y, u != v && dx * dx + dy * dy <= (lo + hi) / 2)
					adj[u].push_back(v);
		if (strong_enough(adj))
			hi = (lo + hi) / 2;
		else
			lo = (lo + hi) / 2 + 1;
	}
	cout << fixed << setprecision(6) << sqrt(lo);
}
