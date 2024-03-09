#include <bits/stdc++.h>
using namespace std;

constexpr int64_t MOD = 1e9 + 7, PHI = MOD - 1;

int64_t mpow(int64_t a, int64_t b)
{
	int64_t ans = 1;
	for (b = (b % PHI + PHI) % PHI; b; b /= 2, a = a * a % MOD)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

int main()
{
	int n;
	cin >> n;
	vector<int64_t> S(n);
	vector<int> K(n);
	for (int i = n - 1; i >= 0; i--)
	{
		cout << "1 1 " << i + 1 << endl;
		cin >> K[i] >> S[i];
	}
	cout << "2 " << S[0];
	vector<int64_t> DP(n + 1, 0);
	DP[0] = 1;
	DP[1] = S[0];
	for (int i = 1; i < n; i++)
	{
		int64_t& s = S[i];
		int k = K[i];
		s = (s + MOD - DP[k]) % MOD;
		s = (s * mpow(DP[k - 1], -1)) % MOD;
		cout << ' ' << s;
		for (int i = n - 1; i > 0; i--)
			DP[i] = (DP[i] + DP[i - 1] * s) % MOD;
	}
}