#include <bits/stdc++.h>

using namespace std;

int n, tim;
vector<vector<int>> G;
vector<unordered_set<int>> B;
vector<int> num, low;

void dfs1(int u, int v)
{
	num[v] = low[v] = tim++;
	for (int w : G[v])
		if (w != u)
		{
			if (num[w] < 0)
			{
				dfs1(v, w);
				low[v] = min(low[v], low[w]);
				if (low[w] > num[v])
				{
					B[v].insert(w);
					B[w].insert(v);
				}
			}
			else
			{
				low[v] = min(low[v], num[w]);
				B[v].erase(w);
				B[w].erase(v);
			}
		}
}

int main()
{
	int m;
	cin >> n >> m;
	n++;
	G.resize(n);
	B.resize(n);
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		u++;
		v++;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	num.resize(n, -1);
	low.resize(n);
	dfs1(0, 0);

	vector<int> st{ 0 };
	vector<bool> V(n);
	vector<int> VV;
	vector<pair<int, int>> S;
	while (!st.empty())
	{
		int v = st.back();
		st.pop_back();
		if (V[v]) continue;
		V[v] = true;
		VV.push_back(v);
		for (int w : G[v])
		{
			if (B[v].find(w) != B[v].end())
				S.emplace_back(v, w);
			else if (!V[w])
				st.push_back(w);
		}
	}
	for (int v : VV)
		V[v] = false;
	VV.clear();

	int ans = 0;

	for (auto [u, v] : S)
	{
		VV.push_back(u);
		V[u] = true;
		st.push_back(v);
		while (!st.empty())
		{
			int w = st.back();
			st.pop_back();
			if (V[w])
				continue;
			V[w] = true;
			VV.push_back(w);
			for (int x : G[w])
				if (!V[x])
					st.push_back(x);
		}
		ans = max(ans, (int)VV.size() - 1);
		for (int w : VV)
			V[w] = false;
		VV.clear();
	}

	cout << ans;
}