#include <bits/stdc++.h>

using namespace std;

int main()
{
	int64_t a, b, c, d, l;
	cin >> a >> b >> c >> d;
	c /= gcd(c, d);
	l = c * d;
	cout << (l / d != c ? 0 : b / l - (a - 1) / l);
}