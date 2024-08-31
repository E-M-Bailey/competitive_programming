#pragma GCC optimize("no-stack-protector,unroll-loops")
#pragma GCC target("avx2,fma")

#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	// cin >> tc;
	while (tc--)
		go();
}

double const EPS = 5e-8;

alignas(32) double X[1 << 17], X2[1 << 17], Y[1 << 17], R[1 << 17];

void go()
{
	int n;
	cin >> n;
	// int N = (n + 3) / 4;
	for (int i = 0; i < n; i++)
		cin >> X[i] >> Y[i] >> R[i];
	fill(begin(R) + n, end(R), numeric_limits<double>::infinity());

	auto const f = [&](double y)
	{
		__m256d sy = _mm256_set1_pd(y);
		__m256d dd = _mm256_set1_pd(numeric_limits<double>::infinity());
		__m256d dv = dd;
		for (int i = 0; i < 25000; i++)
		{
			__m256d dx2 = _mm256_load_pd(X2 + 4 * i);
			__m256d dy	= _mm256_load_pd(Y + 4 * i);
			dy			= _mm256_sub_pd(dy, sy);
			__m256d rr	= _mm256_load_pd(R + 4 * i);
			__m256d hyp = _mm256_sqrt_pd(_mm256_fmadd_pd(dy, dy, dx2));
			__m256d cur = _mm256_sub_pd(rr, hyp);
			__m256d msk = _mm256_cmp_pd(cur, dd, _CMP_LT_OS);
			__m256d cdv = _mm256_div_pd(dy, hyp);
			dd			= _mm256_blendv_pd(dd, cur, msk);
			dv			= _mm256_blendv_pd(dv, cdv, msk);

			// dd			= _mm256_min_pd(dd, cur);
		}
		alignas(32) double ans[4], adv[4];
		_mm256_store_pd(ans, dd);
		_mm256_store_pd(adv, dv);
		int i = int(min_element(begin(ans), end(ans)) - begin(ans));
		return pair{ans[i], adv[i]};
	};

	auto const solve_y = [&](double x)
	{
		for (int i = 0; i < 100000; i++)
		{
			double dx = X[i] - x;
			X2[i]	  = dx * dx;
		}
		double lo = -1e6, hi = 1e6;
		while (hi - lo > EPS)
		{
			// double a = (lo * 33 + hi * 31) / 64, b = (lo * 31 + hi * 33) / 64;
			// double p = f(x, a), q = f(x, b);
			// if (p <= q)
			// 	lo = a;
			// else
			// 	hi = b;
			double a = (lo + hi) / 2;
			if (f(a).second > 0)
				lo = a;
			else
				hi = a;
		}
		double y = (lo + hi) / 2;
		return pair{f(y).first, y};
	};

	double lo = -1e6, hi = 1e6;
	while (hi - lo > EPS)
	{
		double a = (lo * 33 + hi * 31) / 64, b = (lo * 31 + hi * 33) / 64;
		double p = solve_y(a).first, q = solve_y(b).first;
		if (p <= q)
			lo = a;
		else
			hi = b;
	}

	double x	= (lo + hi) / 2;
	auto [r, y] = solve_y(x);

	cout << fixed << setprecision(9) << x << ' ' << y << ' ' << r;

	/*
	vector<double> A(n), B(n);

	auto const solve = [&](double y)
	{
		vector<tuple<double, double, double>> L;
		for (int i = 0; i < n; i++)
		{
			auto [X, Y, R] = C[i];
			double dy	   = y - Y;
			double a = -2 * X, b = X * X + dy * dy - R * R;
			while (!L.empty())
			{
				auto [t, c, d] = L.back();
				double da = a - c, db = b - d;
				if (da == 0)
				{
					if (db <= 0)
						break;
				}
				else
				{
					double s = -db / da;
					if (s > t)
					{
						L.emplace_back(s, a, b);
						break;
					}
				}
				L.pop_back();
			}
			if (L.empty())
				L.emplace_back(-numeric_limits<double>::infinity(), a, b);
		}
		int m = (int)size(L);

		pair<double, double> ans{numeric_limits<double>::infinity(), 0};

		for (int i = 0; i < m; i++)
		{
			auto [s, a, b] = L[i];
			double t	   = i == m - 1 ? numeric_limits<double>::infinity() : get<0>(L[i + 1]);
			double c	   = -a / 2;
			if (s <= c && c <= t)
				ans = min(ans, pair{(c + a) * c + b, c});
			else
				ans = min(ans, min(pair{(s + a) * s + b, s}, pair{(t + a) * t + b, t}));
		}

		return ans;
	};

	double lo = -1e6, hi = 1e6;;
	while (hi - lo > 1e-8)
	{
		double a = (lo * 2 + hi) / 3, b = (lo + hi * 2) / 3;
		auto [sa, xa] = solve(a);
		auto [sb, xb] = solve(b);
		if (sa <= sb)
			hi = b;
		else
			lo = a;
	}

	double y = (lo + hi) / 2;
	auto [x, r] = solve(y);
	r = -r;
	*/
}
