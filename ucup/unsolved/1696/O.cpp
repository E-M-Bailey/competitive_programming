#include <bits/stdc++.h>

using namespace std;

int main()
{
	long double a, b;
	int	   n;
	long double x, z;
	cin >> a >> b >> n >> x >> z;
	swap(a, b);
	vector<pair<long double, long double>> C(2);
	C[0] = {1, 0};
	C[1] = {0, 1};
	while (size(C) < n)
	{
		auto [c, d] = C[size(C) - 2];
		auto [e, f] = C[size(C) - 1];
		C.emplace_back(c * a + e * b, d * a + f * b);
	}
	auto [p, q] = C.back();
	long double y = (z - p * x) / q;
	cout << fixed << setprecision(8);
	for (auto [c, d] : C)
	{
		cout << c * x + d * y << '\n';
	}
}