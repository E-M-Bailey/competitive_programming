#include <bits/stdc++.h>

using namespace std;

int constexpr MOD = 1000000007;

vector<vector<vector<array<int, 3>>>> F;

int f(int ka, int kb, int kc, int g)
{
	if (min({ka, kb, kc}) < 0 || max({ka, kb, kc}) == 0)
		return 0;

	int &dp = F[ka][kb][kc][g];
	if (dp < 0)
	{
		if (ka + kb + kc == 1)
			dp = g == 0 ? ka : g == 1 ? kb : kc;
		else
		{
			if (g == 0)
				dp = f(ka - 1, kb, kc, 1) + f(ka - 1, kb, kc, 2);
			else if (g == 1)
				dp = f(ka, kb - 1, kc, 0) + f(ka, kb - 1, kc, 2);
			else
				dp = f(ka, kb, kc - 1, 0) + f(ka, kb, kc - 1, 1);
			if (dp >= MOD)
				dp -= MOD;
		}
	}
	return dp;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, T;
	cin >> n >> T;
	vector<int> A, B, C;
	while (n--)
	{
		int t, g;
		cin >> t >> g;
		(g == 1 ? A : g == 2 ? B : C).push_back(t);
	}

	int na = (int)size(A), nb = (int)size(B), nc = (int)size(C);

	vector<vector<vector<int>>> KAB(na + 1, vector<vector<int>>(nb + 1, vector<int>(2501)));
	KAB[0][0][0] = 1;
	for (int ta : A)
		for (int ka = na + 1; ka-- > 1;)
			for (int kb = nb + 1; kb-- > 0;)
				for (int s = 2501; s-- > ta;)
					if ((KAB[ka][kb][s] += KAB[ka - 1][kb][s - ta]) >= MOD)
						KAB[ka][kb][s] -= MOD;
	for (int tb : B)
		for (int ka = na + 1; ka-- > 0;)
			for (int kb = nb + 1; kb-- > 1;)
				for (int s = 2501; s-- > tb;)
					if ((KAB[ka][kb][s] += KAB[ka][kb - 1][s - tb]) >= MOD)
						KAB[ka][kb][s] -= MOD;

	vector<vector<int>> KC(nc + 1, vector<int>(2501));
	KC[0][0] = 1;
	for (int tc : C)
		for (int kc = nc + 1; kc-- > 1;)
			for (int s = 2501; s-- > tc;)
				if ((KC[kc][s] += KC[kc - 1][s - tc]) >= MOD)
					KC[kc][s] -= MOD;
	// KC.insert(begin(KC), vector<int>(2501));
	// for (int kc = 1; kc < nc + 2; kc++)
	// 	for (int s = 0; s < 2501; s++)
	// 		if ((KC[kc][s] += KC[kc - 1][s]) >= MOD)
	// 			KC[kc][s] -= MOD;

	vector<int> fac(51);
	fac[0] = 1;
	for (int i = 1; i < 51; i++)
		fac[i] = int((long long)fac[i - 1] * i % MOD);

	F.assign(na + 1, vector<vector<array<int, 3>>>(nb + 1, vector<array<int, 3>>(nc + 1, {-1, -1, -1})));

	int ans = 0;

	for (int ka = 0; ka <= na; ka++)
		for (int kb = 0; kb <= nb; kb++)
			for (int kc = 0; kc <= nc; kc++)
				if (max({ka, kb, kc}) * 2 <= ka + kb + kc + 1)
					for (int s = 0; s < 2501; s++)
					{
						int		  t = T - s;
						long long x = ((long long)f(ka, kb, kc, 0) + f(ka, kb, kc, 1) + f(ka, kb, kc, 2)) % MOD * fac[ka] % MOD * fac[kb] % MOD * fac[kc] % MOD;
						if (0 <= t && t < 2501)
							ans = int((ans + x * KAB[ka][kb][s] % MOD * KC[kc][t]) % MOD);
					}
	// {
	// 	int mc = min(max(0, max(ka, kb) - min(ka, kb) - 1), nc + 1), Mc = min(ka + kb + 2, nc + 1);
	// 	if (mc >= Mc)
	// 		continue;
	// 	for (int s = 0; s < 2501; s++)
	// 	{
	// 		int t = T - s;
	// 		if (t < 0 || t >= 2501)
	// 			continue;

	// 		ans = int((ans + (long long)KAB[ka][kb][s] * (PC[Mc][t] - PC[mc][t] + MOD)) % MOD);
	// 	}
	// }

	cout << ans;
}
