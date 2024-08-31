#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<int> a(n);
		for (int i = 0; i<n; i++) {
			cin >> a[i];
		}
		n++;
		vector<vector<int>> graph(n);
		for (int i = 0; i<n-1; i++) {
			int u,v;
			cin >> u >> v;
			graph[--u].push_back(--v);
			graph[v].push_back(u);
		}
		vector<vector<int>> dist(n, vector<int>(n, 1e9 + 10)), par(n, vector<int>(n, -1));
		pair<int, int> diameter{0, 0};
		int dd = 0;
		for (int i = 0; i<n; i++) {
			queue<int> q;
			dist[i][i] = 0;
			q.push(0);
			while (!q.empty()) {
				auto curr = q.front();
				q.pop();
				for (auto neighbor : graph[curr]) {
					if (dist[i][neighbor] > dist[i][curr] + 1) {
						dist[i][neighbor] = dist[i][curr] + 1;
						par[i][neighbor] = curr;
						q.push(neighbor);
					}
				}
			}
			for (int j = 0; j<n; j++) {
				if (dist[i][j] > dd) {
					dd = dist[i][j];
					diameter = make_pair(i, j);
				}
			}
		}
		vector<int> path;
		while (diameter.second != -1) {
			path.push_back(diameter.second);
			diameter.second = par[diameter.first][diameter.second];
		}
		int m = int(path.size());
		vector<vector<vector<int>>> dp(n-1, vector<vector<int>>(n, vector<int>(n,-1)));
		function<int(int,int,int)> solve = [&](int i, int j, int rem) {
			if (dp[rem][i][j] != -1) return dp[rem][i][j];
			for (auto neighbor : graph[path[i]]) {

			}
		};
	}
}