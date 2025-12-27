#include <bits/stdc++.h>

using namespace std;

// Source: KACTL
struct Dinic
{
	struct Edge
	{
		int		  to, rev;
		long long c, oc;
		long long flow()
		{
			return max(oc - c, 0ll);
		}
	};
	vector<int>			 lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, long long c, long long rcap = 0)
	{
		adj[a].push_back({b, (int)size(adj[b]), c, c});
		adj[b].push_back({a, (int)size(adj[a]) - 1, rcap, rcap});
	}
	long long dfs(int v, int t, long long f)
	{
		if (v == t || !f)
			return f;
		for (int &i = ptr[v]; i < (int)size(adj[v]); i++)
		{
			Edge &e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (long long p = dfs(e.to, t, min(f, e.c)))
				{
					e.c -= p;
					adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	long long calc(int s, int t)
	{
		long long flow = 0;
		q[0]		   = s;
		for (int L = 0; L < 31; L++)
			do
			{
				lvl = ptr = vector<int>(size(q));
				int qi = 0, qe = lvl[s] = 1;
				while (qi < qe && !lvl[t])
				{
					int v = q[qi++];
					for (Edge e : adj[v])
						if (!lvl[e.to] && e.c >> (30 - L))
						{
							q[qe++]	  = e.to;
							lvl[e.to] = lvl[v] + 1;
						}
				}
				while (long long p = dfs(s, t, LLONG_MAX))
					flow += p;
			}
			while (lvl[t]);
		return flow;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int								  n, m;
	vector<int>						  A, ans;
	vector<tuple<int, int, int, int>> E;

	A.reserve(100);
	ans.reserve(1000);
	E.reserve(1000);

	while (cin >> n, n >= 0)
	{
		cin >> m;
		A.resize(n);
		ans.resize(m);
		E.clear();
		for (int &a : A)
			cin >> a;
		for (int i = 0; i < m; i++)
		{
			int a, b;
			cin >> a >> b;
			if (a == n || b == n)
			{
				A[n - 1] += 2;
				ans[i] = b == n ? 2 : 0;
			}
			else
				E.emplace_back(a - 1, b - 1, i, -1);
		}
		int k = (int)E.size();

		if (*max_element(begin(A), end(A) - 1) >= A[n - 1])
		{
			cout << "NO\n";
			continue;
		}

		int	  N = k + n + 1;
		int	  s = N - 2, t = N - 1;
		Dinic D(N);
		for (int i = 0; i < k; i++)
		{
			auto &[a, b, id, eid] = E[i];

			D.addEdge(s, i, 2);
			D.addEdge(i, a + k, 2);
			eid = (int)D.adj[i].size();
			D.addEdge(i, b + k, 2);
		}
		for (int i = 0; i < n - 1; i++)
			if (A[i] < A[n - 1])
				D.addEdge(i + k, t, A[n - 1] - A[i] - 1);

		if (D.calc(s, t) < 2 * k)
		{
			cout << "NO\n";
			continue;
		}

		for (int i = 0; i < k; i++)
		{
			auto [a, b, id, eid] = E[i];

			ans[id] = (int)D.adj[i][eid].flow();
		}

		for (int a : ans)
			cout << a << ' ';
		cout << '\n';
	}
}
