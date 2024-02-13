#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int			  ct = 0;
	ostringstream out;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			int a;
			cin >> a;
			ct += a >= 0;
			if (a >= 0)
				out << i << ' ' << j << ' ' << a << '\n';
		}
	cout << ct << '\n' << out.str();
}
