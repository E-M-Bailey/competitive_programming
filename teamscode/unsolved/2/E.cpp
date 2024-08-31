#include <bits/stdc++.h>

using namespace std;

constexpr long long BIG = 2000000010;

long long smul(long long a, long long b)
{
	auto ans = (long long)a * b;
	return (long long)min(ans, (long long)BIG);
}

long long spow(long long a, long long b)
{
	long long ans = 1;
	// if (a <= 1 || b == 0)
	// 	return b == 0 ? 1 : a;
	// if (a >= BIG || b >= 30)
	// 	return BIG;
	for (; b; b /= 2, a = smul(a, a))
		if (b % 2)
			ans = smul(ans, a);
	return ans;
}

int main()
{
	long long T;
	cin >> T;
	while (T--)
	{
		long long a, b, c, ans;
		long long n;
		cin >> a >> b >> c >> n;
		ans				 = n * a;
		auto const solve = [c, n](long long p, long long y) -> long long
		{
			long long lo = y, hi = BIG;
			while (lo < hi)
			{
				long long z = (lo + hi) / 2;
				long long q = z / y, r = z % y;
				long long cur = smul(spow(1 + q, y - r), spow(2 + q, r));
				if (cur >= p)
					hi = z;
				else
					lo = z + 1;
			}
			return lo * c;
		};
		for (long long x = 1; x * x <= n + 10; x++)
		{
			long long x2 = (n + x - 1) / x;
			for (long long y = 1; y < 40; y++)
			{
				if (a * x + b * y < ans)
					ans = min(ans, a * x + b * y + solve(x2, y));
				if (a * x2 < ans)
					ans = min(ans, a * x2 + b * y + solve(x, y));
			}
		}
		cout << ans << '\n';
		// for (int x = 1; x <= (int)min(b + c + 10, (long long)n); x++)
		// {
		// 	int y = (n + x - 1) / x;

		// }
		// for (int k = 0; (1 << k) < n * 2; k++)
		// {
		// 	int x = (n + (1 << k) - 1) >> k;
		// 	c = min(c, x * a + k * b);
		// }
		// cout << c << '\n';
	}
}
