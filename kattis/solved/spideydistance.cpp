#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int64_t t, s;
	cin >> t >> s;
	int64_t n = 0, d = 0;
	for (int x = 0; x <= s; x++)
	{
		int64_t sh = max(2 * min(s - (x + 1) / 2, 2 * (s - x)) + 1, (int64_t)0);
		int64_t th = max(min(sh, 2 * (t - x) + 1), (int64_t)0);
		int		m  = x ? 2 : 1;
		n += m * th;
		d += m * sh;
	}
	int64_t g = gcd(n, d);
	n /= g;
	d /= g;
	cout << n;
	if (d > 1)
		cout << '/' << d;
}
