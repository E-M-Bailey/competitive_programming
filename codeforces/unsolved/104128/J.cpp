#include <bits/stdc++.h>

using namespace std;

int cc(unordered_map<int, int> &X, int x)
{
	return X.try_emplace(x, (int)size(X)).first->second;
}

int dfs(int									  i,
		int									  v,
		int									  d,
		vector<vector<pair<int, int>>> const &G,
		vector<bool>						 &VV,
		vector<bool>						 &VE,
		vector<set<pair<int, int>>>			 &CH,
		vector<vector<pair<int, int>>>		 &BE,
		vector<int>							 &D,
		vector<pair<int, int>>				 &P,
		vector<int>							 &CD,
		vector<int>							 &BD)
{
	D[v]	= d;
	VV[v]	= true;
	VE[i]	= true;
	int ans = 0;
	for (auto ed : G[v])
	{
		auto [w, j] = ed;
		if (j == i)
		{
			P[v] = ed;
			continue;
		}
		if (VV[w] && !VE[j])
		{
			ans++;
			BE[v].push_back(ed);
			BD[v]++;
		}
		if (!VV[w])
		{
			ans++;
			CH[v].insert(ed);
			CD[v]++;
			ans += dfs(j, w, d + 1, G, VV, VE, CH, BE, D, P, CD, BD);
		}
	}
	return ans;
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n;
		cin >> n;
		unordered_map<int, int> X, Y;
		vector<pair<int, int>>	E;

		for (int i = 0; i < n; i++)
		{
			int a;
			cin >> a;
			int x = cc(X, a - i), y = cc(Y, a + i);
			E.emplace_back(x, y);
		}

		int p = (int)size(X), q = (int)size(Y), N = p + q;

		vector<vector<pair<int, int>>> G(n);
		for (int i = 0; i < n; i++)
		{
			auto [u, v] = E[i];
			v += p;
			G[u].emplace_back(v, i);
			G[v].emplace_back(u, i);
		}

		vector<set<pair<int, int>>>	   CH(N);
		vector<vector<pair<int, int>>> BE(N);
		vector<pair<int, int>>		   P(N);
		vector<int>					   D(N), CD(N), BD(N);
		bool						   good = true;
		{
			vector<bool> VV(N), VE(n);
			for (int i = 0; i < N; i++)
				if (!VV[i])
					good &= dfs(-1, i, 0, G, VV, VE, CH, BE, D, P, CD, BD) % 2 == 0;
		}

		if (!good)
		{
			cout << "No\n";
			continue;
		}

		priority_queue<tuple<int, int, int>> L;
		for (int i = 0; i < N; i++)
			if (CD[i] == 0)
				L.emplace(D[i], BD[i], i);

		vector<pair<int, int>> ans;

		while (!L.empty())
		{
			auto [d, bd, v] = L.top();
			L.pop();
			auto [u, k] = P[v];

			if (bd > 1)
			{
				int i = BE[v].back().second;
				BE[v].pop_back();
				int j = BE[v].back().second;
				BE[v].pop_back();
				bd -= 2;
				L.emplace(d, bd, v);
				ans.emplace_back(i, j);
				continue;
			}
			if (bd == 1)
			{
				int i = BE[v][0].second;
				BE[v].clear();
				int j = k;
				bd--;
				CH[u].erase({v, j});
				if (--CD[u] == 0)
					L.emplace(D[u], BD[u], u);
				ans.emplace_back(i, j);
				continue;
			}
			if (CD[u] > 1)
			{
				int	 i	= k;
				auto it = begin(CH[u]);
				if (it->second == i)
					++it;
				int j = it->second;
				CH[u].erase({v, i});
				CH[u].erase(it);
				if ((CD[u] -= 2) == 0)
					L.emplace(D[u], BD[u], u);
				ans.emplace_back(k, j);
				continue;
			}
			if (BD[u] > 1)
			{
				int i = k;
				int j = BE[u].back().second;
				BE[u].pop_back();
				CH[u].erase({v, i});
				BD[u]--;
				if (--CD[u] == 0)
					L.emplace(D[u], BD[u], u);
				ans.emplace_back(i, j);
				continue;
			}
			else
			{
				
			}
		}
	}
}