#include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1001113;

int main()
{
	vector<vector<int>> DP(101);
	DP[1].resize(1, 1);
	for (int N = 1; N < 100; N++)
	{
		DP[N + 1].resize(N + 1);
		for (int v = 0; v < N; v++)
		{
			DP[N + 1][v]	 = (DP[N + 1][v] + DP[N][v] * (v + 1)) % MOD;
			DP[N + 1][v + 1] = (DP[N + 1][v + 1] + DP[N][v] * (N - v)) % MOD;
		}
	}

	int T;
	cin >> T;
	while (T--)
	{
		int K, N, v;
		cin >> K >> N >> v;
		cout << K << ' ' << DP[N][v] << '\n';
	}
}
