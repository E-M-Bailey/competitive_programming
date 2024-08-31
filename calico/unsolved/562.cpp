#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int b, l, e;
		cin >> b >> l >> e;
		b = ((-b - e) % 50 + 50) % 50;
		cout << (b + l) / 50 + (b == 0) << '\n';
	}
}