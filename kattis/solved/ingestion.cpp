#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	vector<int> C{m};
	while (C.back() > 0)
		C.push_back(C.back() * 2 / 3);
	int					k = size(C);
	vector<vector<int>> DP(n + 1, vector<int>(k));
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < k; j++)
		{
			int &dp = DP[i][j] = INT_MIN;
			int	 c			   = min(C[j], A[i - 1]);
			if (i == 1 && j == 0)
			{
				dp = c;
				continue;
			}
			if (j > 0)
				dp = max(dp, DP[i - 1][j - 1] + c);
			if (i > 1)
				dp = max(dp, DP[i - 2][j] + c);
			if (i > 2 && j == 0)
				for (int l = 0; l < k; l++)
					dp = max(dp, DP[i - 3][l] + c);
		}
	int ans = 0;
	for (int j = 0; j < k; j++)
		ans = max(ans, DP[n][j]);
	cout << ans;
}
