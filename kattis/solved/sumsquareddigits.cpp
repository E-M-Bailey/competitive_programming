#include <bits/stdc++.h>

using namespace std;

int main()
{
	int p;
	cin >> p;
	while (p--)
	{
		int k, b;
		unsigned n;
		cin >> k >> b >> n;
		int x = 0;
		while (n)
		{
			x += (n % b) * (n % b);
			n /= b;
		}
		cout << k << ' ' << x << '\n';
	}
}
