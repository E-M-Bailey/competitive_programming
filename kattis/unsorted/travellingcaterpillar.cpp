#include <bits/stdc++.h>

using namespace std;

vector<bool> A;
vector<vector<pair<int, int>>> ch;

pair<bool, int> dfs(int v)
{
	bool need = A[v];
	int ans = 0;
	for (auto [w, d] : ch[v])
	{
		auto [need2, ans2] = dfs(w);
		if (need2)
		{
			need = true;
			ans += d * 2 + ans2;
		}
	}
	return { need, ans };
}

int main()
{
	int n, k;
	cin >> n >> k;
	ch.resize(n);
	for (int i = 1; i < n; i++)
	{
		int u, v, d;
		cin >> u >> v >> d;
		ch[u].emplace_back(v, d);
	}
	A.resize(n);
	while (k--)
	{
		int a;
		cin >> a;
		A[a] = true;
	}

	cout << dfs(0).second;
}