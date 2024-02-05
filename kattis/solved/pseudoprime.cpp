#include <bits/stdc++.h>

using namespace std;

int64_t pow(int64_t a, int64_t b, int64_t mod)
{
	if (b == 0)
		return 1;
	int64_t ans = pow(a, b / 2, mod);
	ans			= ans * ans % mod;
	if (b % 2)
		ans = ans * a % mod;
	return ans;
}

bool prime(int64_t p)
{
	if (p <= 1)
		return false;
	for (int64_t i = 2; i * i <= p; i++)
		if (p % i == 0)
			return false;
	return true;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int64_t p, a;
	while (cin >> p >> a && p)
		cout << (pow(a, p, p) == a && !prime(p) ? "yes" : "no") << '\n';
}
