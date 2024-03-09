#include <bits/stdc++.h>

using namespace std;

typedef long double T;

struct tourist
{
	T x, y, w, vx, vy;
	bool reach(T x0, T y0, T t0, T v, T t) const
	{
		T dx = x + vx * t - x0, dy = y + vy * t - y0, d = (t - t0) * v;
		return d * d >= dx * dx + dy * dy;
	}
};

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	while (cin >> n, n)
	{
		T v;
		cin >> v;

		vector<tourist> A(n);
		for (auto &[x, y, w, vx, vy] : A)
		{
			T a;
			cin >> x >> y >> w >> a;
			sincosl(a, &vy, &vx);
			vx *= w;
			vy *= w;
		}

		vector<int> P(n);
		iota(begin(P), end(P), 0);
		T best = numeric_limits<T>::infinity();
		do
		{
			T cur = 0, x = 0, y = 0, t = 0;
			for (int i : P)
			{
				const tourist &a = A[i];
				T lo = t, hi = 1e8l;
				for (int j = 0; j < 70; j++)
				{
					T tt = (lo + hi) / 2;
					if (a.reach(x, y, t, v, tt))
						hi = tt;
					else
						lo = tt;
				}
				t = (lo + hi) / 2;
				x = a.x + a.vx * t;
				y = a.y + a.vy * t;
				cur = max(cur, t + sqrtl(x * x + y * y) / a.w);
			}
			best = min(best, cur);
		} while (next_permutation(begin(P), end(P)));
		cout << roundl(best) << '\n';
	}
}