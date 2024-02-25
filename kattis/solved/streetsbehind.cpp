#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int64_t x, y, a, b;
		cin >> x >> y >> a >> b;
		int64_t c = b - a, ans = 0;
		while (y)
		{
			int64_t d = c * x / a;
			if (d == 0)
			{
				ans = -1;
				break;
			}
			int64_t k = min(((d + 1) * a - c * x - 1) / (c * d) + 1, (y - 1) / d + 1), ch = min(k * d, y);
			ans += k;
			x += ch;
			y -= ch;
		}
		cout << ans << '\n';
	}
}
