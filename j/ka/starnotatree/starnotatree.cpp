#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<complex<double>> X(n);
	for (auto &z : X)
	{
		double a, b;
		cin >> a >> b;
		z = {a, b};
	}
	
	complex<double> a = accumulate(begin(X), end(X), complex<double>(0)) / (double)n;
	double best = 0;
	for (auto z : X)
		best += abs(z - a);

	// Weiszfeld's Algorithm
	for (int i = 0; i < 1000; i++)
	{
		complex<double> num = 0;
		double den = 0;
		double cur = 0;
		for (auto z : X)
		{
			auto dist = abs(z - a);
			if (dist < 1e-9)
				continue;
			cur += dist;
			auto fac = 1 / dist;
			num += z * fac;
			den += fac;
		}
		best = min(best, cur);
		a = num / den;
	}
	cout << fixed << setprecision(7) << best;
}
