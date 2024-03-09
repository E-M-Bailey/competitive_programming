#include <bits/stdc++.h>

using namespace std;

int direct(int64_t n, int64_t d, int64_t b)
{
	int ans = 0;
	while (n)
	{
		ans += n % b == d;
		n /= b;
	}
	return ans;
}

int indirect(int64_t n, int64_t d, int mask) {}

int main()
{
	int64_t n, d;
	cin >> n >> d;

	int ans = 0;
	for (int b = 2; b <= 1000; b++)
		ans = max(ans, direct(n, d, b));
	for (int mask = 1; mask < 64; mask++)
		if (__builtin_popcount(mask) > ans)
			ans = max(ans, indirect(n, d, mask));

	cout << ans;
}
