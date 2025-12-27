#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	while (cin >> n >> m)
	{
		vector<vector<pair<int, int>>> G(n);
		while (m--)
		{
			int u, v, d;
			cin >> u >> v >> d;
			u--;
			v--;
			G[u].emplace_back(v, d);
			G[v].emplace_back(u, d);
		}

		int64_t			BIG = numeric_limits<int64_t>::max();
		vector<int64_t> D(n, BIG);
		D[1] = 0;
		priority_queue<pair<int, int>> Q;
		Q.emplace(0, 1);
		while (!Q.empty())
		{
			auto [d, v] = Q.top();
			Q.pop();
			d *= -1;
			for (auto [w, wt] : G[v])
			{
				if (d + wt >= D[w])
					continue;
				D[w] = d + wt;
				Q.emplace(-D[w], w);
			}
		}

		vector<int> order;
		for (int i = 0; i < n; i++)
			if (i != 1 && D[i] < BIG)
				order.push_back(i);
		sort(begin(order),
			 end(order),
			 [&](int i, int j)
			 {
				 return D[i] < D[j];
			 });

		vector<int64_t> ways(n, 0);
		ways[1] = 1;

		for (int v : order)
			for (auto [w, wt] : G[v])
				if (D[w] < D[v])
					ways[v] += ways[w];

		cout << ways[0] << '\n';
	}
}
