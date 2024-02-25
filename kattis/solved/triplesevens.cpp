#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int x = 0x80;
	for (int i = 0; i < 3; i++)
	{
		int y = 0;
		for (int j = 0; j < n; j++)
		{
			int d;
			cin >> d;
			y |= 1 << d;
		}
		x &= y;
	}
	cout << (x ? "777" : "0");
}