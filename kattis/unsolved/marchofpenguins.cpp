#include <bits/stdc++.h>

using namespace std;

struct dinic
{
	struct edge
	{
		int to, rev;
		long long c, oc;
		long long flow()
		{
			return max(oc - c, 0ll);
		}
	};
	vector<int> lvl, ptr, q;
	vector<vector<edge>> adj;
	dinic(int n) : lvl(n), ptr(n), q(n), adj(n)
	{}

	void add_edge(int a, int b, long long c, long long rcap = 0)
	{
		adj[a].push_back({ b, (int)adj[b].size(), c, c });
		adj[b].push_back({ a, (int)adj[a].size() - 1, rcap, rcap });
	}

	long long dfs(int v, int t, long long f)
	{
		if (v == t || !f)
			return f;
		for (int &i = ptr[v]; i < (int)size(adj[v]); i++)
		{
			edge &e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (long long p = dfs(e.to, t, min(f, e.c)))
				{
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}

	long long calc(int s, int t)
	{
		long long flow = 0;
		q[0] = s;
		for (int L = 0; L < 31; L++)
		{
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
				while (long long p = dfs(s, t, LLONG_MAX))
					flow += p;
			} while (lvl[t]);
		}
		return flow;
	}
};

int main()
{
	int n;
	long double d;
	cin >> n >> d;
	d = d * d + 1e-9l;
	dinic D(n * 2 + 1);
	vector<pair<int, int>> P(n);
	int tot = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> P[i].first >> P[i].second;
		int a, b;
		cin >> a >> b;
		D.add_edge(n * 2, 2 * i, a);
		D.add_edge(2 * i, 2 * i + 1, b);
		for (int j = 0; j < i; j++)
		{
			int dx = P[i].first - P[j].first, dy = P[i].second - P[j].second;
			if (dx * dx + dy * dy <= d)
			{
				D.add_edge(j * 2 + 1, i * 2, 10'000);
				D.add_edge(i * 2 + 1, j * 2, 10'000);
			}
		}
		tot += a;
	}

	bool fnd = false;
	for (int i = 0; i < n; i++)
	{
		dinic E = D;
		auto flow = E.calc(n * 2, 2 * i);
		if (flow >= tot)
		{
			fnd = true;
			cout << i << ' ';
		}
	}
	if (!fnd)
		cout << -1;
}