#include <bits/stdc++.h>

using namespace std;

int main()
{
	double a, b, c, d;
	cin >> a >> b >> c >> d;
	double s = (a + b + c + d) / 2;
	cout << fixed << setprecision(8) << sqrt((a - s) * (b - s) * (c - s) * (d - s));
}