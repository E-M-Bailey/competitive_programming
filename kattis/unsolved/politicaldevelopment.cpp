#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	vector<unordered_set<int>>	   G(n);
	priority_queue<pair<int, int>> Q;
	for (int i = 0; i < n; i++)
	{
		int c;
		cin >> c;
		for (int j = 0; j < c; j++)
		{
			int v;
			cin >> v;
			G[i].insert(v);
		}
		Q.emplace(-c, i);
	}

	int ans = 0;
	while (!Q.empty())
	{
		auto [c, v] = Q.top();
		Q.pop();
		c = -c;
		if (c != (int)size(G[v]))
			continue;

		vector<int> V(begin(G[v]), end(G[v]));
		sort(begin(V), end(V));
		vector<int> A(c);
		for (int i = 0; i < c; i++)
			for (int j = 0; j < c; j++)
				A[i] |= int(G[V[i]].count(V[j])) << j;

		for (int mask = 0; mask < (1 << c); mask++)
		{
			bool good = true;
			for (int i = 0; i < c; i++)
				good &= !(mask & (1 << i)) || mask == (A[i] | 1 << i);
			if (good)
				ans = max(ans, __builtin_popcount(mask));
		}

		for (int u : V)
		{
			G[u].erase(v);
			Q.emplace(-(int)size(G[u]), u);
		}
	}

	cout << ans + 1;
}
