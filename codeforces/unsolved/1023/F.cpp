#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, R, X;
	dso(int n) : P(n), R(n), X(n)
	{
		iota(begin(P), end(P), 0);
		iota(begin(X), end(X), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = pair{P[x], P[P[x]]};
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		X[y] = X[x];
		if (R[x] < R[y])
			swap(x, y);
		R[x] += R[x] == R[y];
		P[y] = x;
		return true;
	}
};

void dfs(int v, vector<vector<int>> const &G, vector<int> &P, vector<int> &D, vector<int> &R, vector<int> &F)
{
	F[R[v]]++;
	for (int w : G[v])
		if (w != P[v])
		{
			P[w] = v;
			D[w] = D[v] + 1;
			R[w] = R[v];
			dfs(w, G, P, D, R, F);
		}
}

void reroot(int v, vector<vector<int>> const &G, vector<int> &P, vector<int> &D, vector<int> &R, vector<int> &F, dso &C)
{
	F[R[v]]++;
	for (int w : G[v])
		if (w != P[v])
		{
			P[w]   = v;
			D[w]   = D[v] + 1;
			R[w]   = R[v];
			C.X[w] = C.find(w) == C.find(v) ? C.X[v] : w;
			reroot(w, G, P, D, R, F, C);
		}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, k, m;
	cin >> n >> k >> m;

	dso					C(n);
	vector<int>			D(n), R(n), P(n), F(n);
	vector<vector<int>> G(n);
	iota(begin(P), end(P), 0);
	iota(begin(R), end(R), 0);
	for (int i = 0; i < k; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for (int i = 0; i < n; i++)
		if (R[i] == i)
			dfs(i, G, P, D, R, F);

	long long ans = 0;
	int		  rem = k;

	for (int i = 0; i < m; i++)
	{
		int u, v, wt;
		cin >> u >> v >> wt;
		u--;
		v--;
		u = C.X[C.find(u)];
		v = C.X[C.find(v)];
		if (R[u] != R[v])
		{
			if (F[R[u]] < F[R[v]])
				swap(u, v);
			G[v].push_back(u);
			G[u].push_back(v);
			P[v]   = u;
			D[v]   = D[u] + 1;
			R[v]   = R[u];
			C.X[v] = u;
			reroot(v, G, P, D, R, F, C);
			C.onion(u, v);
		}
		else
		{
			while (u != v)
			{
				ans += wt;
				rem--;
				if (D[u] > D[v])
					swap(v, u);
				C.onion(P[v], v);
				v = C.X[C.find(v)];
			}
		}
	}

	cout << (rem ? -1 : ans);
}
