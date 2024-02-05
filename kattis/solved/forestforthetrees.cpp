#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int64_t x, y, x1, y1, x2, y2;
	cin >> x >> y >> x1 >> y1 >> x2 >> y2;

	int64_t g  = gcd(x, y);
	int64_t dx = x / g, dy = y / g;
	if (dx < min(x, x1) || dy < min(y, y1))
	{
		cout << "No" << '\n' << dx << ' ' << dy;
		return 0;
	}

	int64_t c  = min(x2 / dx, y2 / dy) + 1;
	int64_t xn = c * dx, yn = c * dy;
	if (xn < x)
	{
		cout << "No" << '\n' << xn << ' ' << yn;
		return 0;
	}
	cout << "Yes";
}
