#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	vector<tuple<char, int, int>> ops;
	for (int q = 0; q < m; q++)
	{
		char c;
		cin >> c;
		if (c == 'q')
		{
			int x, y, z;
			cin >> x >> y >> z;
			x--;
			y--;
			z--;
			for (int i = (int)size(ops); i-- > 0;)
			{
				auto [ch, a, k] = ops[i];
				for (int j = 0; j < a; j++)
				{
					if (ch == 'x' && x >= k)
						tie(z, y) = pair{y, n - 1 - z};
					else if (ch == 'y' && y >= k)
						tie(x, z) = pair{z, n - 1 - x};
					else if (ch == 'z' && z >= k)
						tie(y, x) = pair{x, n - 1 - y};
				}
			}
			cout << 1 + x + n * (y + n * z) << '\n';
		}
		else
		{
			int a, k;
			cin >> a >> k;
			if (a != 360)
				ops.emplace_back(c, a / 90, k);
		}
	}
}
