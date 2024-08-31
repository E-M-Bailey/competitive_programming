#include <bits/stdc++.h>

using namespace std;

void inp(vector<pair<long double, long double>> &X, long double &h)
{
	X.resize(5);
	cin >> X[0].first >> X[0].second >> X[1].first >> X[1].second >> h;
	long double dx = X[1].first - X[0].first, dy = X[1].second - X[0].second;
	X[2] = {X[1].first - dy, X[1].second + dx};
	X[3] = {X[0].first - dy, X[0].second + dx};
	X[4] = X[0];
}

int main()
{
	vector<pair<long double, long double>> A, B;
	long double						 ha, hb;
	inp(A, ha);
	inp(B, hb);

	long double da = hypot(A[1].first - A[0].first, A[1].second - A[0].second);
	long double db = hypot(B[1].first - B[0].first, B[1].second - B[0].second);

	long double best = numeric_limits<long double>::infinity();

	auto const distt = [&](int j, long double xa, long double ya, long double t)
	{
		long double xb = B[j + 1].first * t + B[j].first * (1 - t);
		long double yb = B[j + 1].second * t + B[j].second * (1 - t);
		return hypot(xb - xa, yb - ya) + hypot(db / 2, db * (t - 0.5), hb);
	};
	auto const dists = [&](int i, int j, long double s)
	{
		long double xa = A[i + 1].first * s + A[i].first * (1 - s);
		long double ya = A[i + 1].second * s + A[i].second * (1 - s);

		long double l = 0, r = 1;
		for (int jj = 50; jj-- > 0;)
		{
			long double a = (4 * l + 3 * r) / 7, b = (3 * l + 4 * r) / 7;
			long double aa = distt(j, xa, ya, a), bb = distt(j, xa, ya, b);
			if (aa > bb)
				l = a;
			else
				r = b;
		}
		return distt(j, xa, ya, (l + r) / 2) + hypot(da / 2, da * (s - 0.5), ha);
	};

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			long double l = 0, r = 1;
			for (int ii = 50; ii-- > 0;)
			{
				long double a = (4 * l + 3 * r) / 7, b = (3 * l + 4 * r) / 7;
				long double aa = dists(i, j, a), bb = dists(i, j, b);
				if (aa > bb)
					l = a;
				else
					r = b;
			}
			
			best = min(best, dists(i, j, (l + r) / 2));
		}
	
	cout << fixed << setprecision(8) << best;
}
