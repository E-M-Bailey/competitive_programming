// right side, 6th row, middle table, The University of Texas at Dallas
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

static constexpr const ll inf = 1e15;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, m, k;
		cin >> n >> m >> k;
		vector<bool> is_exit(n);
		for (int i = 0; i < k; i++)
		{
			int e;
			cin >> e;
			is_exit[--e] = true;
		}
		vector<int> d(n);
		for (int i = 0; i < n; i++)
		{
			cin >> d[i];
		}
		vector<vector<pair<int, ll>>> G(n);
		for (int i = 0; i < m; i++)
		{
			int x, y;
			ll	w;
			cin >> x >> y >> w;
			G[--x].emplace_back(--y, w);
			G[y].emplace_back(x, w);
		}
		vector<ll> ret(n, inf);

		priority_queue<pair<ll, int>> Q;
		for (int i = 0; i < n; i++)
		{
			if (is_exit[i])
			{
				Q.emplace(0, i);
				d[i] = 0;
			}
		}
		while (!Q.empty())
		{
			auto [dv, v] = Q.top();
			Q.pop();
			if (d[v]-- != 0)
				continue;
			ret[v] = dv = -dv;
			for (const auto &[w, wt] : G[v])
			{
				if (d[w] < 0)
					continue;
				Q.emplace(-(dv + wt), w);
			}
		}
		if (ret[0] >= inf)
			cout << -1 << '\n';
		else
			cout << ret[0] << '\n';
	}
}