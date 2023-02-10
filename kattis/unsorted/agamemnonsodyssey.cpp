#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int n,k;
    cin >> n >> k;
    using edge_t = pair<int, int>;
    vector<vector<edge_t>> graph(n);

    ll total_weight = 0;

    for (int i = 0; i<n-1; i++) {
        int u,v,c;
        cin >> u >> v >> c;
        graph[--u].emplace_back(--v, c);
        graph[v].emplace_back(u, c);
        total_weight += c * 1ll;
    }

    if (k >= 2) {
        cout << total_weight << '\n';
        return 0;
    }

    vector<ll> dist(n, -1);

    ll ret = 0; //

    function<ll(int, int)> dfs = [&](int curr, int par) {
        if (dist[curr] != -1) return dist[curr];
        vector<ll> paths;
        for (const auto& [neighbor, weight] : graph[curr]) {
            if (neighbor == par) continue;
            paths.push_back(dfs(neighbor, curr) + weight);
        }
        if (paths.empty()) {
            return dist[curr] = 0;
        }
        sort(paths.rbegin(), paths.rend());
        ret = max(ret, paths[0]);
        if (paths.size() > 1) {
            ret = max(ret, paths[0] + paths[1]);
        }
        return dist[curr] = paths[0];
    };

    dfs(0, -1);

    cout << ret << '\n';

}
