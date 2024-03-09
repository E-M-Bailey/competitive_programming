#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1000000007;

int HP[10000001];
vector<int> P;


int64_t mpow(int64_t a, int64_t b)
{
	int64_t ans = 1;
	for (; b; a = a * a % MOD, b /= 2)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}


int main()
{
	for (int i = 2; i <= 10000000; i++)
	{
		if (HP[i])
			continue;
		for (int j = i; j <= 10000000; j += i)
			HP[j] = i;
		P.push_back(i);
	}

	int n;
	while (cin >> n, n)
	{
		int64_t ans = 1;
		for (int p : P)
		{
			int ct = 0;
			for (int64_t pp = p; pp <= n; pp *= p)
				ct += n / (int)pp;
			ans = ans * mpow(p, ct & ~1) % MOD;
		}
		cout << ans << '\n';
	}
}