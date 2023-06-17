#include <bits/stdc++.h>

using namespace std;

constexpr __uint128_t bit(int n)
{
	return __uint128_t(1) << n;
}

int main()
{
	int n;
	while (cin >> n, n >= 0)
	{
		vector<__uint128_t> C(100, 0);
		for (int i = 0; i < n; i++)
		{
			int s, a;
			cin >> s >> a;
			s--;
			a--;
			C[a] |= bit(s);
		}

		int m;
		cin >> m;
		vector<int> S(m);
		for (int &s : S)
		{
			cin >> s;
			s--;
		}

		vector<__uint128_t> CS(100, 0);
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < m - 1; j++)
				if (C[i] & ((bit(S[j + 1]) - 1) ^ (bit(S[j]) - 1)))
					CS[i] |= bit(j);

		int k;
		cin >> k;
		vector<vector<int>> DP(100, vector<int>(k, INT_MIN)), P(100, vector<int>(k));
		DP[0][0] = 0;

		for (int i = 1; i < 100; i++)
		{
			for (int j = 1; j < k; j++)
			{
				__uint128_t row = 0;
				for (int l = i; l-- >= j;)
				{
					row |= CS[l];
					int ct = __builtin_popcountll(uint64_t(row)) + __builtin_popcountll(uint64_t(row >> 64));

					int cur = ct + DP[l][j - 1];
					if (cur >= DP[i][j])
					{
						DP[i][j] = cur;
						P[i][j] = l;
					}
				}
			}
		}

		vector<int> ans(k);
		for (int i = 99, j = k; j-- > 0; i = P[i][j])
			ans[j] = i + 1;

		cout << k;
		for (int a : ans)
			cout << ' ' << a;
		cout << '\n';
	}
}
