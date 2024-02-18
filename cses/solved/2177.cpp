#include <bits/stdc++.h>

using namespace std;

int dfs(vector<vector<int>> const &adj, int u, int v, int &t, vector<int> &num, vector<pair<int, int>> &ans) {
	int low_v = num[v] = t++, low_w;
	for (int w : adj[v])
		if (w == u) {} // skip the parent
		else if (num[w] == -1) { // unvisited
			low_v = min(low_v, low_w = dfs(adj, v, w, t, num, ans));
			if (low_w > num[v]) // bridge => impossible
				t = max(t, (int)adj.size() + 1);
			ans.emplace_back(v, w); // DFS-edge downwards
		}
		else if (low_v = min(low_v, num[w]), num[w] < num[v]) // visited, back-edge upwards
			ans.emplace_back(v, w); // back-edge upwards
	return low_v;	
}
int main() {
	int n, m, t = 0, a, b;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		adj[a - 1].push_back(b - 1);
		adj[b - 1].push_back(a - 1);
	}
	vector<int> num(n, -1);
	vector<pair<int, int>> ans;
	dfs(adj, 0, 0, t, num, ans);
	if (t == n) // Connected and bridgeless
		for (auto [u, v] : ans)
			cout << u + 1 << ' ' << v + 1 << '\n';
	else
		cout << "IMPOSSIBLE";
}