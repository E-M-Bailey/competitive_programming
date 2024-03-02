#include <bits/stdc++.h>

using namespace std;

void dist(int n, int s, vector<vector<pair<int, int>>> const &G, vector<int64_t> &D)
{
	vector<bool> V(n, false);
	priority_queue<pair<int, int>> Q;
	Q.emplace(0, s);
	while (!Q.empty())
	{
		auto [d, v] = Q.top();
		Q.pop();
		if (V[v])
			continue;
		V[v] = true;
		D[v] += d = -d;
		for (auto [w, wt] : G[v])
			if (!V[w])
				Q.emplace(-(wt + d), w);
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;
	vector<int64_t> G(n);
	for (int64_t &g : G)
		cin >> g;
	vector<vector<pair<int, int>>> A(n), B(n);
	for (int i = 0; i < m; i++)
	{
		int u, v, a, b;
		cin >> u >> v >> a >> b;
		u--;
		v--;
		A[u].emplace_back(v, a);
		A[v].emplace_back(u, a);
		B[u].emplace_back(v, b);
		B[v].emplace_back(u, b);
	}
	
	dist(n, 0, A, G);
	dist(n, n - 1, B, G);
	cout << *min_element(begin(G), end(G));
}
