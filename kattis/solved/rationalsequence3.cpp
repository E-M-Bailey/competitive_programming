#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int k, n;
		cin >> k >> n;

		int p = 0, q = 1;

		for (int m = 32 - __builtin_clz(n); m >= 0; m--)
		{
			if (n & (1 << m))
				p += q;
			else
				q += p;
		}

		cout << k << ' ' << p << '/' << q << '\n';
	}
}
