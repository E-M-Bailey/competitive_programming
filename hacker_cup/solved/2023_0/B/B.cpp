#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++)
	{
		int r, c, a, b;
		cin >> r >> c >> a >> b;
		cout << "Case #" << tt << ": " << (r > c ? "YES\n" : "NO\n");
	}
}
