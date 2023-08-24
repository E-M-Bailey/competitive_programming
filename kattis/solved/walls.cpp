#include <bits/stdc++.h>

using namespace std;

int main()
{
	int l, w, n, r2;
	cin >> l >> w >> n >> r2;
	r2 = r2 * r2 * 4;
	pair<int, int> const W[4]{ {-l, 0}, {l, 0}, {0, -w}, {0, w} };

	vector<uint8_t> C(n);
	for (uint8_t &c : C)
	{
		int x, y;
		cin >> x >> y;
		x *= 2;
		y *= 2;
		for (int i = 0; i < 4; i++)
		{
			auto [a, b] = W[i];
			int dx = x - a, dy = y - b;
			if (dx * dx + dy * dy <= r2)
				c |= 1 << i;
		}
	}
	int ans = 5;
	for (int i = 0; i < n; i++)
	{
		int a = C[i];
		if (a == 15)
			ans = min(ans, 1);
		for (int j = i + 1; j < n; j++)
		{
			int b = C[j] | a;
			if (b == 15)
				ans = min(ans, 2);
			for (int k = j + 1; k < n; k++)
			{
				int c = C[k] | b;
				if (c == 15)
					ans = min(ans, 3);
				for (int o = k + 1; o < n; o++)
				{
					int d = C[o] | c;
					if (d == 15)
						ans = min(ans, 4);
				}
			}
		}
	}
	if (ans == 5)
		cout << "Impossible";
	else
		cout << ans;

}