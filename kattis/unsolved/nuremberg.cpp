#include <bits/stdc++.h>

using namespace std;

int n;

struct vert
{
	vector<pair<int, int>> adj{};
	int64_t m = 0, d = 0, m2 = 0, d2 = 0;
};

vector<vert> G;

void dfs1(int u, int v)
{
	for (auto [w, d] : G[v].adj)
	{
		if (w == u)
			continue;
		dfs1(v, w);
		G[v].m += G[w].m;
		G[v].d += G[w].d + d * G[w].m;
	}
}

void dfs2(int u, int v)
{
	for (auto [w, d] : G[v].adj)
	{
		if (w == u)
			continue;
		G[w].m2 = G[v].m2 + G[v].m - G[w].m;
		G[w].d2 = G[v].d + G[v].d2 - G[w].d + d * (G[w].m2 - G[w].m);
		dfs2(v, w);
	}
}

int main()
{
	int c;
	cin >> c;
	while (c--)
	{
		cin >> n;
		G.assign(n, {});
		for (int i = 1; i < n; i++)
		{
			int a, b, t;
			cin >> a >> b >> t;
			a--;
			b--;
			G[a].adj.emplace_back(b, t);
			G[b].adj.emplace_back(a, t);
		}
		int m;
		cin >> m;
		while (m--)
		{
			int a, f;
			cin >> a >> f;
			a--;
			G[a].m = f;
		}

		dfs1(0, 0);
		dfs2(0, 0);

		int64_t best = (int64_t)LLONG_MAX;
		vector<int> V;
		for (int i = 0; i < n; i++)
		{
			//cerr << ' ' << i << ' ' << G[i].d << ' ' << G[i].d2 << endl;
			auto d = G[i].d + G[i].d2;
			if (d < best)
			{
				best = d;
				V.clear();
			}
			if (d == best)
				V.push_back(i);
		}
		sort(begin(V), end(V));
		cout << best * 2 << '\n';
		for (int v : V)
			cout << v + 1 << ' ';
		cout << '\n';
	}

}