#include <bits/stdc++.h>

using namespace std;

void dfs(int v, unordered_map<int, vector<int>> &G, unordered_set<int> &V)
{
	if (!V.insert(v).second)
		return;
	for (int w : G[v])
		dfs(w, G, V);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	unordered_map<int, vector<int>> A, B;
	vector<int>						I;
	for (int i = 0; i < n; i++)
	{
		int u, m;
		cin >> u >> m;
		I.push_back(u);
		for (int j = 0; j < m; j++)
		{
			int v;
			cin >> v;
			A[u].push_back(v);
			B[v].push_back(u);
		}
	}

	bool			   good = true;
	unordered_set<int> VA, VB;
	dfs(0, A, VA);
	dfs(0, B, VB);

	for (int i : I)
		if (VB.find(i) == VB.end())
		{
			good = false;
			cout << "TRAPPED " << i << '\n';
		}
	for (int i : I)
		if (VA.find(i) == VA.end())
		{
			good = false;
			cout << "UNREACHABLE " << i << '\n';
		}
	if (good)
		cout << "NO PROBLEMS" << '\n';
}
