#include <bits/stdc++.h>

using namespace std;

unordered_map<long long, double> DP;

double x, y;

long long A;

double f(long long k)
{
	auto [it, ins] = DP.emplace(k, 0);
	if (!ins)
		return it->second;
	double a = x + f(k / A);
	double b = (f(k / 2) + f(k / 3) + f(k / 4) + f(k / 5) + f(k / 6) + 6 * y) * 0.2;
	return it->second = min(a, b);
}

int main()
{
	long long n;
	cin >> n >> A >> x >> y;
	DP[0] = 0;
	cout << fixed << setprecision(8) << f(n);
}