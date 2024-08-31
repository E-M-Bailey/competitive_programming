// right side, 6th row, middle table, The University of Texas at Dallas
#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

constexpr int M = 998244353;

int main()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<int>									 A(n);
	vector<long long>							 C(n);
	vector<vector<pair<int, int>>>				 G(n);
	vector<vector<pair<int, int>>>				 LG(n);
	vector<set<pair<long long, int>>>			 S(n);
	vector<set<pair<long long, int>>::node_type> F;
	for (int &a : A)
		cin >> a;

	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		u--;
		v--;
		G[u].emplace_back(v, w);
		G[v].emplace_back(u, w);
	}
	for (int i = 0; i < n; i++)
	{
		if ((int)size(G[i]) > 800)
		{
			for (auto [w, wt] : G[i])
			{
				LG[w].emplace_back(i, wt);
				S[i].emplace(wt, w);
			}
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
			F.push_back(S[u].extract({C[v] + wt, v}));
		}
		if ((int)size(G[v]) <= 800)
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
			if (!F.empty())
			{
				F.back().value() = {C[v] + wt, v};
				S[u].insert(move(F.back()));
				F.pop_back();
			}
			else
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
