#include <bits/stdc++.h>

using namespace std;

int main()
{
	/*
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
			{
				int ax = i & 1, ay = i >> 1, bx = j & 1, by = j >> 1, cx = k & 1, cy = k >> 1;
				if ((ax * by + ay * bx + bx * cy + by * cx + cx * ay + by * ax) % 2 == 0)
				{
					cout << "ABCD"[i] << "ABCD"[j] << "ABCD"[k] << '\n';
					ct++;
				}
			}
	*/

	vector<pair<int, int>> A, B, C, D;
	for (int i = 0; i < 1999; i++)
	{
		int x = i - 1000, y = (i * i) % 1999 - 1000;
		(x % 2 ? y % 2 ? D : C : y % 2 ? B : A).emplace_back(x, y);
	}

	// vector<pair<int, int>> ans;
	// auto				   add = [randy = mt19937_64(2024),
	// 			  odd	= uniform_int_distribution<int>(0, 999),
	// 			  even	= uniform_int_distribution<int>(0, 1000),
	// 			  &ans](bool x, bool y) mutable
	// {
	// 	int X = (x ? odd : even)(randy) * 2 - 1000 + x;
	// 	int Y = (y ? odd : even)(randy) * 2 - 1000 + y;
	// 	for (int i = 0; i < (int)size(ans); i++)
	// 	{
	// 		auto [xx, yy] = ans[i];
	// 		if (xx == X && yy == Y)
	// 			return;
	// 		for (int j = 0; j < i; j++)
	// 		{
	// 			auto [xxx, yyy] = ans[j];
	// 			int dx = xx - x, dy = yy - y, dxx = xxx - xx, dyy = yyy - yy;
	// 			if (dx * dyy - dy * dxx == 0)
	// 				return;
	// 		}
	// 	}
	// 	ans.emplace_back(X, Y);
	// };

	int t, tgt;
	cin >> t >> tgt;
	for (int a = 0; a <= min(t, (int)size(A)); a++)
	{
		int ac2 = a * (a - 1) / 2, ac3 = ac2 * (a - 2) / 3, aa = ac2 * (t - a) + ac3;
		for (int b = 0; b <= min(t - a, (int)size(B)); b++)
		{
			int bc2 = b * (b - 1) / 2, bc3 = bc2 * (b - 2) / 3, bb = bc2 * (t - b) + bc3;
			for (int c = max(0, t - a - b - (int)size(D)); c <= min(t - a - b, (int)size(C)); c++)
			{
				int d	= t - a - b - c;
				int cc2 = c * (c - 1) / 2, cc3 = cc2 * (c - 2) / 3, cc = cc2 * (t - c) + cc3;
				int dc2 = d * (d - 1) / 2, dc3 = dc2 * (d - 2) / 3, dd = dc2 * (t - d) + dc3;
				int cur = aa + bb + cc + dd;
				if (cur == tgt)
				{
					for (int i = 0; i < a; i++)
						cout << A[i].first << ' ' << A[i].second << '\n';
					for (int i = 0; i < b; i++)
						cout << B[i].first << ' ' << B[i].second << '\n';
					for (int i = 0; i < c; i++)
						cout << C[i].first << ' ' << C[i].second << '\n';
					for (int i = 0; i < d; i++)
						cout << D[i].first << ' ' << D[i].second << '\n';
					// while ((int)size(ans) < a)
					// 	add(0, 0);
					// while ((int)size(ans) < a + b)
					// 	add(0, 1);
					// while ((int)size(ans) < a + b + c)
					// 	add(1, 0);
					// while ((int)size(ans) < a + b + c + d)
					// 	add(1, 1);
					// for (auto [x, y] : ans)
					// 	cout << x << ' ' << y << '\n';
					return 0;
				}
			}
		}
	}
	cout << "IMPOSSIBLE";
}
