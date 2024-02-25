#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> A(n, vector<int>(m));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			char ch;
			cin >> ch;
			A[i][j] = ch == '1';
		}
	if (n < m)
	{
		vector<vector<int>> B(m, vector<int>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				B[j][i] = A[i][j];
		A = move(B);
		swap(n, m);
	}

	vector<vector<int>> P(n, vector<int>(m + 1));
	for (int i = 0; i < n; i++)
		partial_sum(begin(A[i]), end(A[i]), begin(P[i]) + 1);

	vector<vector<int>> DP(m, vector<int>(m + 1, INT_MAX / 2));
	fill(begin(DP[0]), end(DP[0]), 0);
	for (int i = 0; i < n; i++)
	{
		for (int l = 0; l < m; l++)
			for (int r = l + 1; r <= m; r++)
				DP[l][r] += P[i][m] + r - l + 2 * (P[i][l] - P[i][r]);
		if (i == n - 1)
			break;
		for (int l = 1; l < m; l++)
			for (int r = l + 1; r <= m; r++)
				DP[l][r] = min(DP[l][r], DP[l - 1][r]);
		for (int l = 0; l < m; l++)
			for (int r = l + 2; r <= m; r++)
				DP[l][r] = min(DP[l][r], DP[l][r - 1]);
		for (int l = m; l-- > 1;)
			for (int r = l + 1; r <= m; r++)
				DP[l][r] = min(DP[l][r], DP[l - 1][l]);
	}

	int ans = INT_MAX;
	for (int l = 0; l < m; l++)
		ans = min(ans, DP[l][m]);
	cout << ans;
}
