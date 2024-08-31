#include <bits/stdc++.h>

using namespace std;

double const inf = numeric_limits<double>::infinity(), eps = 1e-7;

int							 n;
vector<pair<double, double>> P;

// double						 solve()
// {
// 	double best = 0;
// 	for (int i = 1; i < n; i++)
// 	{
// 		double l	  = inf;
// 		auto [x0, y0] = P[i];
// 		for (int j = 1; j < n; j++)
// 		{
// 			auto [x, y]	  = P[j];
// 			auto [xx, yy] = P[j - 1];
// 			double cr	  = y * x0 - (y0 - 1) * x;
// 			if (0 <= cr && cr <= x0)
// 				continue;
// 			double lo = 0, hi = 1;
// 			for (int k = 0; k < 40; k++)
// 			{
// 				double t  = (lo + hi) / 2;
// 				double xt = x * t + xx * (1 - t), yt = y * t + yy * (1 - t);
// 				double crt = yt * x0 - (y0 - 1) * xt;
// 				if (0 <= crt && crt <= x0)
// 					lo = t;
// 				else
// 					hi = t;
// 			}
// 			double t = (lo + hi) / 2;
// 			l		 = x * t + xx * (1 - t);
// 			break;
// 		}
// 		best = max(best, l);
// 	}
// 	return best;
// }

double solve(double x1, double y1, double x2, double y2)
{
	double m	  = (y2 - y1) / (x2 - x1);
	double b	  = y1 - m * x1;
	auto [x0, y0] = P[0];

	if (abs(m * x0 + b - y0) > 0.5 + eps)
		return -inf;

	for (int i = 1; i < n; i++)
	{
		auto [xc, yc] = P[i];
		if (abs(m * xc + b - yc) <= 0.5 + eps)
			continue;
		auto [xp, yp] = P[i - 1];

		double lo = 0, hi = 1;
		for (int j = 0; j < 40; j++)
		{
			double t  = (lo + hi) / 2;
			double xt = (1 - t) * xp + t * xc;
			double yt = (1 - t) * yp + t * yc;
			if (abs(m * xt + b - yt) <= 0.5 + eps)
				lo = t;
			else
				hi = t;
		}

		double t = (lo + hi) / 2;
		return (1 - t) * xp + t * xc;
	}

	return inf;
}

int main()
{
	while (cin >> n, n)
	{
		P.resize(n);
		for (auto &[x, y] : P)
		{
			cin >> x >> y;
			y -= 0.5;
		}

		double ans = P[0].first;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
			{
				auto [xi, yi] = P[i];
				auto [xj, yj] = P[j];
				ans			  = max(ans, solve(xi, yi + 0.5, xj, yj + 0.5));
				ans			  = max(ans, solve(xi, yi - 0.5, xj, yj + 0.5));
				ans			  = max(ans, solve(xi, yi + 0.5, xj, yj - 0.5));
				ans			  = max(ans, solve(xi, yi - 0.5, xj, yj - 0.5));
			}

		if (ans == inf)
			cout << "Through all the pipe.\n";
		else
			cout << fixed << setprecision(2) << ans << '\n';
	}
}
