#include <bits/stdc++.h>

using namespace std;

struct edge
{
	int v, t, p, d;
	int next(int q)
	{
		if (p == 0)
			return q > t ? -1 : t;
		q += ((t - q) % p + p) % p;
		return max(q, t);
	}
};

int main()
{
	int n, m, q, s;
	while (cin >> n >> m >> q >> s, n)
	{

		vector<vector<edge>> G(n);
		while (m--)
		{
			int u, v, t, p, d;
			cin >> u >> v >> t >> p >> d;
			G[u].push_back({ v, t, p, d });
		}

		vector<int> D(n, -1);
		D[s] = 0;
		priority_queue<pair<int, int>> PQ;
		PQ.emplace(0, s);
		while (!PQ.empty())
		{
			auto [d, v] = PQ.top();
			d = -d;
			PQ.pop();
			if (d != D[v])
				continue;

			for (edge e : G[v])
			{
				int w = e.v, dw = e.next(d) + e.d;
				if (dw < e.d || (D[w] >= 0 && D[w] <= dw))
					continue;
				D[w] = dw;
				PQ.emplace(-dw, w);
			}
		}

		while (q--)
		{
			int v;
			cin >> v;
			if (D[v] < 0)
				cout << "Impossible\n";
			else
				cout << D[v] << '\n';
		}
		cout << '\n';
	}
}