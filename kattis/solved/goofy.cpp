#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	while (n--)
	{
		long double x, y;
		cin >> x >> y;
		complex z(x, y);
		long double	theta = arg(z), phi = acos(1 / abs(z));
		complex z1 = polar(1.l, theta + phi), z2 = polar(1.l, theta - phi);
		cout << fixed << setprecision(10) << '(' << real(z1) << ',' << imag(z1) << ",1," << real(z2) << ',' << imag(z2) << ",1)\n";
	}
}
