#include <bits/stdc++.h>

using namespace std;

int main()
{
	int w, h, n;
	cin >> w >> h >> n;
	double s = (double)h / w, g = (1 - s * s);
	double r  = sqrt(1 - g * g);
	double l1 = g / (1 - r), l2 = g / (1 + r), mul = w / (pow(l1, n + 1) - pow(l2, n + 1));

	double ans = (s + 1) * w;
	ans *= ans / 2;
	for (int i = 1; i <= n; i++)
	{
		double a = pow(l1, i) - pow(l2, i), b = pow(l1, i + 1) - pow(l2, i + 1);
		ans += a * (a - b * g) * mul * mul;
	}

	cout << fixed << setprecision(6) << ans / 2 << '\n';
	for (int i = 1; i <= min(n, 10); i++)
		cout << (pow(l1, i) - pow(l2, i)) * mul << '\n';
}
