// right side, 6th row, middle table, The University of Texas at Dallas
#include <bits/stdc++.h>

using namespace std;

constexpr int M = 998244353;

int main()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<int>					   A(n);
	vector<long long>			   C(n), D;
	vector<vector<pair<int, int>>> G(n);
	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}

	vector<vector<int>> B(n);
	int					k = 0;
	for (int i = 0; i < n; i++)
	{
		if ((int)size(G[i]) <= 400)
			continue;
		B[i].resize(((int)size(G[i]) + 399) / 400);
		for (int &b : B[i])
			b = k++;
	}
	D.resize(k);
	for (int &a : A)
		cin >> a;

	vector<vector<int>> H(n);
	for (int v = 0; v < n; v++)
	{
		if ((int)size(G[v]) <= 400)
			continue;
		for (int i = 0; i < (int)size(G[v]); i++)
		{
			int j = i / 400, b = B[v][i];
			auto [w, wt] = G[v][i];
			H[w].emplace_back(b, wt);
		}
	}

	vector<int> Q(q);
	for (int &x : Q)
	{
		cin >> x;
		x--;
	}
	while (!Q.empty())
	{
		int v = Q.back();
		Q.pop_back();

		



		for (auto [u, wt] : LG[v])
		{
			S[u].erase({C[v] + wt, v});
		}
		if ((int)size(G[v]) <= 400)
		{
			C[v] = LLONG_MAX;
			for (auto [w, wt] : G[v])
				C[v] = min(C[v], C[w] + wt);
		}
		else
		{
			C[v] = S[v].begin()->first;
		}
		for (auto [u, wt] : LG[v])
		{
			S[u].emplace(C[v] + wt, v);
		}
	}

	long long ans = 0;
	for (int i = 0; i < n; i++)
	{
		ans = (ans + C[i] % M * A[i]) % M;
	}
	cout << ans;
}
