#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1000000007;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int m, h;
		cin >> m >> h;
		int64_t DP[h + 2];
		DP[0] = 1;
		for (int i = 1; i <= h + 1; i++)
		{
			DP[i] = 0;
			for (int j = i; j-- > max(i - 1 - m, 0);)
				DP[i] += DP[j];
			DP[i] = (DP[i] * 2 + MOD - DP[i - 1]) % MOD * DP[i - 1] % MOD;
		}
		cout << DP[h + 1] << '\n';
	}
}
