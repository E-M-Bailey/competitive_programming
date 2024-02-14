#include <bits/stdc++.h>

using namespace std;

vector<int>						A;
vector<vector<vector<int64_t>>> DP;

int64_t g(int i, int k, int c)
{
	if (i == 0)
		return k == 0 && c == 0 ? 0 : INT64_MIN;
	int64_t &dp = DP[i][k][c];
	if (dp == -1)
	{
		dp = g(i - 1, k, c);
		if (c - i + k >= 0)
			dp = max(dp, g(i - 1, k - 1, c - i + k) + A[i - 1]);
	}
	return dp;
}

int main()
{
	int		n, f;
	int64_t t;
	cin >> n >> f >> t;
	A.resize(n);
	for (auto &a : A)
		cin >> a;
	DP.assign(n + 1, vector<vector<int64_t>>(f + 1, vector<int64_t>(n * f + 1, -1)));
	for (int c = 0; c <= n * f; c++)
		if (g(n, f, c) >= t)
		{
			cout << c;
			return 0;
		}
	cout << "NO";
}
