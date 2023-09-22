#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct dinic
{
	struct edge
	{
		int v, r;
		ll c, f = 0;
		edge(int V, int R, ll C) :
			v(V),
			r(R),
			c(C)
		{}
	};
	vector<int> L, I;
	queue<int> Q;
	vector<vector<edge>> A;
	dinic(int n) : L(n), I(n), A(n) {}

	void add(int u, int v, ll c, ll rc)
	{
		int iu = (int)A[u].size(), iv = (int)A[v].size();
		A[u].emplace_back(v, iv, c);
		A[v].emplace_back(u, iu, rc);
	}

	ll dfs(int v, int t, ll amt)
	{
		if (amt == 0 || v == t)
			return amt;
		for (int &i = I[v]; i < (int)A[v].size(); i++)
		{
			auto &[w, j, c, f] = A[v][i];
			if (f < c && L[w] == L[v] + 1)
			{
				if (ll ans = dfs(w, t, min(amt, c - f)); ans != 0)
				{
					f += ans;
					A[w][j].f -= ans;
					return ans;
				}
			}
		}
		return 0;
	}

	void bfs(int s)
	{
		fill(begin(L), end(L), -1);
		L[s] = 0;
		Q.push(s);
		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for (auto [w, i, c, f] : A[v])
				if (f < c && L[w] == -1)
				{
					L[w] = L[v] + 1;
					Q.push(w);
				}
		}
	}

	ll operator()(int s, int t)
	{
		ll ans = 0;
		while (bfs(s), L[t] != -1)
		{
			fill(begin(I), end(I), 0);
			ll amt;
			while (amt = dfs(s, t, LLONG_MAX), amt != 0)
				ans += amt;
		}
		return ans;
	}
};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;
	vector<string> S(n);
	for (string &s : S)
		cin >> s;
	int m = (int)S[0].size();

	vector<vector<bool>> adj(n, vector<bool>(n));
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			int ct = 0;
			for (int k = 0; k < m; k++)
				ct += S[i][k] != S[j][k];
			adj[i][j] = adj[j][i] = ct == 2;
		}

	vector<bool> A(n), B(n);
	vector<int> ST;
	for (int i = 0; i < n; i++)
		if (!A[i] && !B[i])
		{
			A[i] = true;
			ST.push_back(i);
			while (!ST.empty())
			{
				int v = ST.back();
				ST.pop_back();
				for (int w = 0; w < n; w++)
					if (adj[v][w] && !A[w] && !B[w])
					{
						A[w] = B[v];
						B[w] = A[v];
						ST.push_back(w);
					}
			}
		}

	dinic D(n + 2);
	for (int i = 0; i < n; i++)
		if (A[i])
		{
			D.add(n, i, 1, 0);
			for (int j = 0; j < n; j++)
				if (adj[i][j] && B[j])
					D.add(i, j, 1, 0);
		}
		else
			D.add(i, n + 1, 1, 0);

	cout << n - D(n, n + 1);
}