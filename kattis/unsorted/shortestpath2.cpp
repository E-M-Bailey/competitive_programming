#include <bits/stdc++.h>

using namespace std;

struct Edge {
	int w;
	int t0, P, e;
};

constexpr int iinf = 1e9 + 10;

int main(int argc, const char* argv[]) {
	if (argc > 1) {
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	while (true) {
		int n,m,q,s;
		cin >> n >> m >> q >> s;
		if (!n && !m && !q && !s) {
			break;
		}
		vector<vector<Edge>> graph(n);
		for (int i = 0; i<m; i++) {
			int u,v, t0, P, e; 
			cin >> u >> v >> t0 >> P >> e;
			graph[u].push_back({v, t0, P, e});
		}

		vector<int> dist(n, iinf);
		dist[s] = 0;
		auto cmp = [&](int x, int y) {
			if (dist[x] != dist[y]) return dist[x] < dist[y];
			return x < y;
		};

		set<int, decltype(cmp)> pq(cmp);
		pq.insert(s);

		while (!pq.empty()) {
			auto curr = *pq.begin();
			pq.erase(pq.begin());

			for (auto[w, t0, P, e] : graph[curr]) {
				auto dw = 0;
				if (P) {
					dw = (max(0, dist[curr] - t0) + P - 1) / P;
					dw = dw * P + t0 + e;
				} else {
					dw = (dist[curr] <= t0 ? t0 : iinf) + e;
				}
				if (dist[w] > dw) {
					pq.erase(w);
					dist[w] = dw;
					pq.insert(w);
				}
			}
		}

		while (q--) {
			int t; cin >> t;
			if (dist[t] == iinf) cout << "Impossible" << '\n';
			else cout << dist[t] << '\n';
		}

		cout << '\n';




	}

}