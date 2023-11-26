#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int x = 1000000000, X = 0, y = 1000000000, Y = 0;
	while (n--)
	{
		int xx, yy;
		cin >> xx >> yy;
		x = min(x, xx);
		X = max(X, xx);
		y = min(y, yy);
		Y = max(Y, yy);
	}
	cout << (X - x + Y - y + 4) * 2;
}