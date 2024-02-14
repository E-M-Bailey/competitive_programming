#include <bits/stdc++.h>

using namespace std;

// Source: KACTL
struct dinic
{
	struct edge
	{
		int to, rev;
		int c, oc;
		int flow()
		{
			return max(oc - c, 0);
		}
	};
	vector<int>			 lvl, ptr, q;
	vector<vector<edge>> adj;
	dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void add_edge(int a, int b, int c, int rcap = 0)
	{
		adj[a].push_back({b, (int)size(adj[b]), c, c});
		adj[b].push_back({a, (int)size(adj[a]) - 1, rcap, rcap});
	}
	int dfs(int v, int t, int f)
	{
		if (v == t || !f)
			return f;
		for (int &i = ptr[v]; i < (int)size(adj[v]); i++)
		{
			edge &e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (int p = dfs(e.to, t, min(f, e.c)))
				{
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	int calc(int s, int t)
	{
		int flow = 0;
		q[0]	 = s;
		for (int L = 0; L < 31; L++)
			do
			{
				lvl = ptr = vector<int>(size(q));
				int qi = 0, qe = lvl[s] = 1;
				while (qi < qe && !lvl[t])
				{
					int v = q[qi++];
					for (edge e : adj[v])
						if (!lvl[e.to] && e.c >> (30 - L))
							q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
				}
				while (int p = dfs(s, t, INT_MAX))
					flow += p;
			}
			while (lvl[t]);
		return flow;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	dinic D(n);
	while (m--)
	{
		int u, v, c;
		cin >> u >> v >> c;
		D.add_edge(u, v, c);
	}

	cout << n << ' ' << D.calc(s, t);
	vector<tuple<int, int, int>> E;
	for (int u = 0; u < n; u++)
		for (dinic::edge e : D.adj[u])
			if (int x = e.flow())
				E.emplace_back(u, e.to, x);
	cout << ' ' << size(E) << '\n';
	for (auto [u, v, x] : E)
		cout << u << ' ' << v << ' ' << x << '\n';
}
