// right side, 6th row, middle table, The University of Texas at Dallas
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr const ll inf = 1e15;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n,m,k;
		cin >> n >> m >> k;
		vector<bool> is_exit(n);
		for (int i = 0; i<k; i++) {
			int e;
			cin >> e;
			is_exit[--e] = true;
		}
		vector<int> d(n);
		for (int i = 0; i<n; i++) {
			cin >> d[i];
		}
		vector<vector<pair<int,ll>>> graph(n);
		vector<unordered_map<int, int>> ecnt(n);
		vector<unordered_map<int, multiset<ll>>> de(n);
		for (int i = 0; i<m; i++) {
			int x,y;
			ll w;
			cin >> x >> y >> w;
			graph[--x].emplace_back(--y, w);
			graph[y].emplace_back(x, w);
			ecnt[x][y]++, ecnt[y][x]++;
		}
		vector<ll> ret(n, inf);
		vector<bool> marked(n, false);
		vector<multiset<pair<ll, int>>> dd(n);
		auto cmp = [&](int x, int y) {
			auto dx = *prev(end(dd[x]));
			auto dy = *prev(end(dd[y]));
			if (dx != dy) return dx < dy;
			return x < y;
		};
		set<int, decltype(cmp)> q(cmp);
		for (int i = 0; i<n; i++) {
			if (is_exit[i]) {
				dd[i].emplace(0, -1);
				q.insert(i);
			}
		}
		while (!q.empty()) {
			auto curr = *q.begin();
			q.erase(q.begin());
			marked[curr] = true;
			ret[curr] = prev(end(dd[curr]))->first;
			for (const auto& [neighbor, weight] : graph[curr]) {
				if (marked[neighbor]) continue;
				if (int(dd[neighbor].size()) > d[neighbor]) {
					q.erase(neighbor);
				}
				if (int(de[neighbor][curr].size()) == ecnt[neighbor][curr]) {
					de[neighbor][curr].insert(ret[curr] + weight);
					dd[neighbor].emplace(ret[curr] + weight, curr);
					auto v = *prev(end(de[neighbor][curr]));
					dd[neighbor].erase(dd[neighbor].lower_bound(make_pair(v, curr)));
					de[neighbor][curr].erase(prev(end(de[neighbor][curr])));
				} else {
					de[neighbor][curr].insert(ret[curr] + weight);
					dd[neighbor].emplace(ret[curr] + weight, curr);
				}
				if (int(dd[neighbor].size()) > d[neighbor] + 1) {
					auto [v, par] = *prev(end(dd[neighbor]));
					dd[neighbor].erase(prev(end(dd[neighbor])));
					de[neighbor][par].erase(de[neighbor][par].lower_bound(v));
				}
				if (int(dd[neighbor].size()) > d[neighbor]) {
					q.insert(neighbor);
				}
			}
		}
		if (ret[0] >= inf) cout << -1 << '\n';
		else cout << ret[0] << '\n';
	}
}