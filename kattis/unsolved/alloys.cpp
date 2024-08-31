#include <bits/stdc++.h>

using namespace std;

int main()
{
	long double c;
	cin >> c;
	c = min(c, 1.l);
	cout << fixed << setprecision(20) << c * c / 4;
}
