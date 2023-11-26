#include <bits/stdc++.h>

using namespace std;

long double const R = 6378137;

int main()
{
	long double F, G, T, a, dx, dy;
	cin >> F >> G >> T;
	a = G * T / R;
	dx = R * cosl(a) - R;
	dy = R * sinl(a) - F * T;
	cout << fixed << setprecision(7) << sqrtl(dx * dx + dy * dy);
}