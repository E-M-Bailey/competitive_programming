#include <bits/stdc++.h>

#define len(x) int((x).size())

using namespace std;

int main(int argc, const char* argv[]) {
	if (argc >= 3) {
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n,k; cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i<n; i++) {
		cin >> a[i];
	}
	bool possible = true;
	vector<vector<vector<int>>> bucket(n + 1);
	vector<bool> visited(n, false);
	vector<int> cycle, ret(n, -1);

	function<void(int)> dfs = [&](int curr) {
		visited[curr] = true;
		cycle.push_back(curr);
		auto nxt = a[curr] - 1;
		if (!visited[nxt]) dfs(nxt);
	};

	for (int i = 0; i<n && possible; i++) {
		if (!visited[i]) {
			dfs(i);
			bucket[len(cycle)].push_back(cycle);
			cycle.clear();
		}
	}

	for (int l = 1; l <= n; l++) {
		if (k % l == 0) {
			if (len(bucket[l]) % k) {
				possible = false;
				break;
			}
			for (int i = 0; i<len(bucket[l]); i += k) {
				vector<int> p(l * k, -1);
				for (int j = i; j<i+k; j++) {
					int prv = j - i;
					p[prv] = bucket[l][j][0];
					for (int z = 1; z < l; z++) {
						auto pos = (prv + k) % len(p);
						assert(p[pos] == -1);
						p[pos] = bucket[l][j][z];
						prv = pos;
					}
				}
				for (int j = 0; j < len(p); j++) {
					ret[p[j]] = p[(j + 1) % len(p)] + 1;
				}
			}
		} else {
			for (int i = 0; i<len(bucket[l]); i++) {
				vector<int> p(l, -1);
				int prv = 0;
				p[prv] = bucket[l][i][0];
				for (int j = 1; j < l; j++) {
					auto pos = (prv + k) % len(p);
					assert(p[pos] == -1);
					p[pos] = bucket[l][i][j];
					prv = pos;
				}
				for (int j = 0; j<len(p); j++) {
					ret[p[j]] = p[(j+1) % len(p)] + 1;
				}
			}
		}
	}

	if (!possible) {
		cout << "Impossible" << '\n';
	} else {
		for (auto v : ret) cout << v << " ";
		cout << '\n';
	}

	
	return 0;
}