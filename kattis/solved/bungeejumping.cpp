#include <bits/stdc++.h>

using namespace std;

double const g = 9.81, hpi = atan(1.) * 2;

int main()
{
	double k, l, s, w;
	while (cin >> k >> l >> s >> w, k)
	{
		double const a = sqrt(w / k), c = sqrt(g * w * (2 * l * k + g * w)) / k, d = g * w / k, y0 = s - l, eq = y0 - d, y1 = eq - c;
		cout << (y1 > 0														   ? "Stuck in the air.\n"
				 : (y0 > 0 ? sqrt(c * c - eq * eq) / a : sqrt(2 * g * s)) > 10 ? "Killed by the impact.\n"
																			   : "James Bond survives.\n");
	}
}
