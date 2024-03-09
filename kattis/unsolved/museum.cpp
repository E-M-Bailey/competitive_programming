#include <bits/stdc++.h>

using namespace std;

bool isect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	//cerr << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << x3 << ' ' << y3 << ' ' << x4 << ' ' << y4 << endl;
	if (x1 == x2)
		return x3 <= x1 && x1 <= x4;
	if (y1 == y2)
		return y3 <= y1 && y1 <= y4;

	double xlo, xhi, ylo, yhi;
	tie(xlo, xhi) = minmax((x3 - x1) / (x2 - x1), (x4 - x1) / (x2 - x1));
	tie(ylo, yhi) = minmax((y3 - y1) / (y2 - y1), (y4 - y1) / (y2 - y1));
	//cerr << ' ' << xlo << ' ' << ylo << ' ' << xhi << ' ' << yhi << endl;
	double lo = max({ xlo, ylo, 0. }), hi = min({ xhi, yhi, 1. });
	return lo <= hi;
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int l, w;
		cin >> l >> w;

		vector<pair<double, double>> V;
		for (int x = 0; x <= l; x++)
		{
			V.emplace_back(x, 0);
			V.emplace_back(x, w);
		}
		for (int y = 1; y < w; y++)
		{
			V.emplace_back(0, y);
			V.emplace_back(l, y);
		}

		double X, Y, W;
		cin >> X >> Y >> W;

		int n = (int)V.size();

		vector<vector<bool>> G(n, vector<bool>(n));

		for (int i = 0; i < n; i++)
		{
			auto [x1, y1] = V[i];
			for (int j = i + 1; j < n; j++)
			{
				auto [x2, y2] = V[j];
				G[i][j] = G[j][i] = !isect(x1, y1, x2, y2, X, Y, X + W, Y + W);
				//if (!isect(x1, y1, x2, y2, X, Y, X + W, Y + W))
				//	cerr << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
			}
		}

		int ans = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				for (int k = j + 1; k < n; k++)
				{
					auto [x1, y1] = V[i];
					auto [x2, y2] = V[j];
					auto [x3, y3] = V[k];
					if ((x2 - x1) * (y3 - y1) != (x3 - x1) * (y2 - y1))
						ans += G[i][j] && G[j][k] && G[k][i];
				}
		cout << ans << '\n';
	}
}