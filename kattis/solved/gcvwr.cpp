#include <bits/stdc++.h>

using namespace std;

int main()
{
	int g, t, n;
	cin >> g >> t >> n;
	g -= t;
	g = g * 9 / 10;
	while (n--)
	{
		int w;
		cin >> w;
		g -= w;
	}
	cout << g;
}
