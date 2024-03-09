#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> G(n);
	for (int i = 0; i < m; i++)
	{
		int a, b, wt;
		cin >> a >> b >> wt;
		G[a].emplace_back(b, wt);
		G[b].emplace_back(a, wt);
	}

	const auto dists = [&](int s)
	{
		vector<int> D(n, INT_MAX / 2);
		priority_queue<pair<int, int>> PQ;

		PQ.emplace(0, s);
		while (!PQ.empty())
		{
			auto [d, v] = PQ.top();
			PQ.pop();
			d *= -1;
			if (D[v] == INT_MAX / 2)
			{
				D[v] = d;
				for (auto [w, wt] : G[v])
					if (D[w] == INT_MAX / 2)
						PQ.emplace(-(d + wt), w);
			}
		}

		return D;
	};

	vector<int> D1 = dists(0), D2 = dists(n - 1);
	int dst = D1[n - 1];
	int ans = 0;
	for (int v = 0; v < n; v++)
	{
		if (D1[v] + D2[v] != dst)
			continue;
		for (auto [w, wt] : G[v])
			if (D1[w] + D2[w] == dst && D1[w] - D1[v] == wt)
				ans += wt;
	}

	cout << 2 * ans << '\n';
}