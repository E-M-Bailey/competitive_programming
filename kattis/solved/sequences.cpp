#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD  = 1000000007;
int64_t constexpr INV4 = 250000002;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int64_t c1 = 0, cq = 0, c10 = 0, cq0_1q = 0;
	string	s;
	cin >> s;
	for (char c : s)
	{
		if (c == '0')
		{
			c10 += c1;
			if (c10 >= MOD)
				c10 -= MOD;
			cq0_1q += cq;
			if (cq0_1q >= MOD)
				cq0_1q -= MOD;
		}
		else if (c == '1')
		{
			c1++;
		}
		else
		{
			cq0_1q += c1;
			if (cq0_1q >= MOD)
				cq0_1q -= MOD;
			cq++;
		}
	}

	if (cq == 0)
	{
		cout << c10;
		return 0;
	}

	int64_t p2qm1 = 1;
	for (int64_t a = 2, b = cq - 1; b; a = a * a % MOD, b /= 2)
		if (b % 2)
			p2qm1 = p2qm1 * a % MOD;

	cout << ((c10 * p2qm1 * 2 % MOD + cq0_1q * p2qm1) % MOD + cq * (cq - 1) % MOD * p2qm1 % MOD * INV4) % MOD;
}
