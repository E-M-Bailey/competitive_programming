#include <bits/stdc++.h>

using namespace std;

int main()
{
	int a, b, m, s;
	cin >> a >> b >> m >> s;
	pair<double, double> sols[]
	{
		{1, 1},
		{1, m - 1},
		{1, s - 2},
		{m - 1, 1},
		{(s - 1) * .5, 1},
		{s - m, 2 * m - s}
	};

	int R = 0;
	for (auto [x, y] : sols)
	{
		if (x < 1 || y < 1 || x + y > m || 2 * x + y < s)
			continue;
		//cerr << x << ' ' << y << ' ' << a * x + b * y << endl;
		R = max(R, (int)(a * x + b * y));
	}
	cout << R;
}