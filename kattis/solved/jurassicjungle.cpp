#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int m, n;
	while (cin >> n >> m, m >= 0)
	{
		if (m == n)
		{
			cout << "YES" << '\n';
			for (int i = 1; i < n; i++)
				cout << i << ' ' << i + 1 << '\n';
			cout << "1 " << n << '\n';
		}
		else if (m == n * (n - 1) / 2)
		{
			cout << "YES" << '\n';
			for (int i = 1; i < n; i++)
				for (int j = i + 1; j <= n; j++)
					cout << i << ' ' << j << '\n';
		}
		else if (n % 2 == 0 && m == n * n / 4)
		{
			cout << "YES" << '\n';
			for (int i = 1; i <= n / 2; i++)
				for (int j = n / 2 + 1; j <= n; j++)
					cout << i << ' ' << j << '\n';
		}
		else
			cout << "NO" << '\n';
	}
}
