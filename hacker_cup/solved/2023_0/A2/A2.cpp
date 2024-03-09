#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++)
	{
		int64_t a, b, c;
		cin >> a >> b >> c;
		cout << "Case #" << tt << ": " << max({
			c / a, // Singles
			c / b * 2 - 1, // Doubles
			c < a ? 0 : (c - a) / b * 2 + 1, // One Single
			c < 2 * a ? 0 : (c - 2 * a) / b * 2 + 2 // Two Singles
			}) << '\n';
	}
}
