#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++)
	{
		int s, d, k;
		cin >> s >> d >> k;
		cout << "Case #" << tt << ": " << (min(2 * (s + d) - 1, s + 2 * d) >= k ? "YES\n" : "NO\n");
	}
}
