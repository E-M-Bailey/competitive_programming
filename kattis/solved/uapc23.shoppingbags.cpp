#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> DP;
int t, N1, N2, s1, s2;

int dp(int n1, int n2)
{
	n1 = max(n1, 0);
	n2 = max(n2, 0);
	if (DP[n1][n2] >= 0)
		return DP[n1][n2];
	if (max(n1, n2) == 0)
		return DP[n1][n2] = 0;
	DP[n1][n2] = numeric_limits<int>::max() / 2;
	for (int i = 0; i * s2 <= t; i++)
	{
		int j = (t - i * s2) / s1;
		int m1 = max(n1 - j, 0);
		int m2 = max(n2 - i, 0);
		DP[n1][n2] = min(DP[n1][n2], dp(m1, m2) + 1);
	}
	return DP[n1][n2];
}

int main()
{
	cin >> t >> N1 >> N2 >> s1 >> s2;
	DP.assign(N1 + 1, vector<int>(N2 + 1, -1));
	cout << dp(N1, N2) << endl;
}