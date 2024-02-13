#include <bits/stdc++.h>

using namespace std;

int main()
{
	int l, d, x, m;
	cin >> l >> d >> x;
	bool done = false;
	for (int i = l; i <= d; i++)
	{
		int sum = 0;
		for (int j = i; j; j /= 10)
			sum += j % 10;
		if (sum == x)
		{
			if (!done)
			{
				cout << i << '\n';
				done = true;
			}
			m = i;
		}
	}
	cout << m;
}
