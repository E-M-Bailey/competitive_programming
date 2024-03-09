#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		vector<int> A(n);
		for (int& a : A)
			cin >> a;
		vector<vector<int>> S(n, vector<int>(n));
		vector<vector<int>> DP(n, vector<int>(n));
		for (int i = 0; i < n; i++)
		{
			S[i][i] = A[i];
			DP[i][i] = 0;
		}
		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = i + 1; j < n; j++)
			{
				S[i][j] = (S[i][j - 1] + A[j]) % 100;
				DP[i][j] = INT_MAX;
				for (int k = i + 1; k <= j; k++)
					DP[i][j] = min(DP[i][j], DP[i][k - 1] + DP[k][j] + S[i][k - 1] * S[k][j]);
			}
		}
		cout << DP[0][n - 1] << '\n';
	}
}