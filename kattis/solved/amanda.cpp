#include <bits/stdc++.h>

using namespace std;

bool dfs(vector<vector<int>> const &G, vector<int> &C, int k, int v)
{
	C[v] = k;
	bool ans = true;
	for (int w : G[v])
	{
		if (C[w] < 0)
			ans &= dfs(G, C, k ^ 1, w);
		else
			ans &= C[w] != k;
	}
	return ans;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n + 2);
	G[0].push_back(1);
	G[1].push_back(0);
	while (m--)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a++;
		b++;
		if (c == 0)
		{
			G[1].push_back(a);
			G[1].push_back(b);
			G[a].push_back(1);
			G[b].push_back(1);
		}
		else if (c == 1)
		{
			G[a].push_back(b);
			G[b].push_back(a);
		}
		else
		{
			G[0].push_back(a);
			G[0].push_back(b);
			G[a].push_back(0);
			G[b].push_back(0);
		}
	}
	vector<int> C(n + 2, -1);
	int k = 0;
	for (int i = 0; i < n + 2; i++)
	{
		if (C[i] >= 0)
			continue;
		if (!dfs(G, C, k, i))
		{
			cout << "impossible";
			return 0;
		}
		k += 2;
	}
	vector<int> F(k);
	for (int c : C)
		F[c]++;
	int ans = F[1] - 1;
	for (int i = 2; i < k; i += 2)
		ans += min(F[i], F[i + 1]);
	cout << ans;
}