#include <bits/stdc++.h>

using namespace std;

int main()
{
	int64_t n;
	cin >> n;
	int64_t best = LLONG_MAX;
	int64_t d = 0;
	while (d * d * 2 < n)
		d++;
	while (d * d <= 2 * n)
	{
		int64_t a = max(d, (n + d - 1) / d);
		if (a <= 2 * d)
			best = min(best, a * d - n);
		d++;
	}
	cout << best;
}