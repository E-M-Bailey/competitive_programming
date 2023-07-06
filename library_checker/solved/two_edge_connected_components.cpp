#include <bits/stdc++.h>

using namespace std;

int dfs1(vector<vector<int>> const &adj, int u, int v, int &t, vector<int> &num, vector<unordered_set<int>> &bridges) {
	int low_v = num[v] = t++, low_w;
	for (int w : adj[v])
		if (w == u) {} // skip the parent
		else if (num[w] == -1) { // unvisited
			low_v = min(low_v, low_w = dfs1(adj, v, w, t, num, bridges));
			if (low_w > num[v]) // bridge
				bridges[min(v, w)].insert(max(v, w));
		}
		else { // back-edge or repeated edge
			low_v = min(low_v, num[w]);
			bridges[min(v, w)].erase(max(v, w)); // repeated edges aren't bridges
		}
	return low_v;
}
void dfs2(vector<vector<int>> const &G, vector<unordered_set<int>> const &br, int v, vector<int> &vis, unordered_set<int> &A) {
	vis[v] = true;
	for (int w : G[v])
		if (!br[min(v, w)].contains(max(v, w)) && A.insert(w).second) // skip visited vertices and bridges
			dfs2(G, br, w, vis, A);
}
int main() {
	int n, m, t = 0, a, b;
	cin >> n >> m;
	vector<vector<int>> adj(n);
	for (int i = 0; i < m; i++)
		cin >> a >> b, adj[a].push_back(b), adj[b].push_back(a);
	vector<unordered_set<int>> bridges(n), ans;
	vector<int> num(n, -1), vis(n);
	for (int v = 0; v < n; v++) // find bridges
		if (num[v] == -1) dfs1(adj, v, v, t, num, bridges);
	for (int v = 0; v < n; v++) if (!vis[v]) { // find components
			ans.push_back({ v });
			dfs2(adj, bridges, v, vis, ans.back());
		}
	cout << ans.size() << '\n';
	for (unordered_set<int> const &comp : ans) {
		cout << comp.size();
		for (int v : comp) cout << ' ' << v;
		cout << '\n';
	}
}