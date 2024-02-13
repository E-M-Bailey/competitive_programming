#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	double hi = 3 * (n - k), lo = -hi;
	while (k--)
	{
		int r;
		cin >> r;
		hi += r;
		lo += r;
	}
	cout << fixed << setprecision(5) << lo / n << ' ' << hi / n;
}
