#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int>			C(n);
	vector<vector<int>> IC(k);
	for (int i = 0; i < n; i++)
	{
		cin >> C[i];
		C[i]--;
		IC[C[i]].push_back(i);
	}
	vector<vector<vector<int>>> G(k, vector<vector<int>>(n));
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		G[C[b]][a].push_back(b);
		G[C[a]][b].push_back(a);
	}

	int64_t			ans = 0;
	vector<int64_t> DP(n);
	vector<int>		P;
	for (int mask = 1; mask < 1 << k; mask++)
		if (mask & (mask - 1))
		{
			P.clear();
			for (int i = 0; i < k; i++)
				if (mask & (1 << i))
					P.push_back(i);
			do
			{
				for (int i = 0; i < n; i++)
					DP[i] = C[i] == P[0];
				for (int i = 1; i < (int)P.size(); i++)
					for (int j : IC[P[i]])
						for (int l : G[P[i - 1]][j])
							DP[j] += DP[l];
				for (int i : IC[P.back()])
					ans += DP[i];
			}
			while (next_permutation(begin(P), end(P)));
		}
	cout << ans;
}
