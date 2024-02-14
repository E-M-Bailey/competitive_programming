#include <bits/stdc++.h>

using namespace std;

double const EPS = 1e-10;

double minimize(double d, double c, double b, double a)
{
	double lo = min(d, d + c + b + a);
	if (abs(a) >= EPS)
	{
		double discr = 4 * b * b - 12 * a * c;
		double f	 = 1 / (6 * a);
		double x = -2 * b * f, y = sqrt(max(discr, 0.)) * f;
		if (0 < x - y && x - y < 1)
			lo = min(lo, d + (x - y) * (c + (x - y) * (b + (x - y) * a)));
		if (0 < x + y && x + y < 1)
			lo = min(lo, d + (x + y) * (c + (x + y) * (b + (x + y) * a)));
	}
	else if (abs(b) >= EPS)
	{
		double x = -c / (2 * b);
		if (0 < x && x < 1)
			lo = min(lo, d + x * (c + x * (b + x * a)));
	}
	return lo;
}

int main()
{
	double d, c, b, a, d1, c1, b1, a1;
	while (cin >> d >> c >> b >> a >> d1 >> c1 >> b1 >> a1)
	{
		d -= d1;
		c -= c1;
		b -= b1;
		a -= a1;
		d -= minimize(d, c, b, a);
		cout << fixed << setprecision(8) << -minimize(-d, -c, -b, -a) << '\n';
	}
}
