#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}

	vector<int> dist(n, -1);
	dist[0] = 0;
	queue<int> Q;
	Q.push(0);
	int d = 0;
	while (!Q.empty())
	{
		int sz = (int)Q.size();
		d++;
		while (sz--)
		{
			int v = Q.front();
			Q.pop();
			for (int w : G[v])
				if (dist[w] < 0)
				{
					dist[w] = d;
					Q.push(w);
				}
		}
	}

	auto const cmp = [&](pair<int, int> a, pair<int, int> b)
		{
			return make_tuple(dist[a.second], a.second, a.first) > make_tuple(dist[b.second], b.second, b.first);
		};

	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> PQ(cmp);
	for (int w : G[0])
		PQ.emplace(0, w);

	vector<vector<int>> P(n);
	vector<int> dep(n, -1);
	dep[0] = 0;
	int prv = 0;
	int64_t dis = 0;
	while (!PQ.empty())
	{
		auto [a, b] = PQ.top();
		PQ.pop();
		if (dep[b] >= 0 || dist[b] != dist[a] + 1)
			continue;
		dep[b] = dep[a] + 1;
		P[b].push_back(a);
		while (P[P[b].back()].size() >= P[b].size())
			P[b].push_back(P[P[b].back()][P[b].size() - 1]);

		int x = b, dx = dep[b], y = prv, dy = dep[y];
		while (dx > dy)
		{
			int i = __builtin_ctz(dx - dy);
			dx -= 1 << i;
			dis += 1 << i;
			x = P[x][i];
		}
		while (dx < dy)
		{
			int i = __builtin_ctz(dy - dx);
			dy -= 1 << i;
			dis += 1 << i;
			y = P[y][i];
		}
		while (x != y)
		{
			int i = (int)P[x].size() - 1;
			while (i > 0 && P[x][i] == P[y][i])
				i--;
			dis += 2 << i;
			x = P[x][i];
			y = P[y][i];
		}
		for (int w : G[b])
			PQ.emplace(b, w);
		prv = b;
	}
	cout << dis;
}