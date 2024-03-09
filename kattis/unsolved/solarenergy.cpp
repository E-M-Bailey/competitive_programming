#include <bits/stdc++.h>

using namespace std;

typedef long double T;

const T PI2 = atanl(1) * 8;

// t - s * min(a, 1 - a) < 0
// t < s * min(a, 1 - a)
// t < s * a and t < s * (1 - a)
// t / s < a < 1 - t / s

int main()
{
	int n;
	cin >> n;

	vector<pair<T, T>> ent;
	T y = 0, m = 0;
	for (int i = 0; i < n; i++)
	{
		T t, s, a;
		cin >> t >> s >> a;
		a /= PI2;
		s *= PI2;
		if (s == 0)
		{
			y += t;
			continue;
		}

		T d = t / s;

		T b, c;
		if (d >= 0.5l)
		{
			b = c = a + 0.5l;
		}
		else
		{
			b = a + d;
			c = a + 1 - d;
		}
		b = fmod(b, 1);
		c = fmod(c, 1);

		if (c > a)
		{
			y += t - s * a;
			m += s;
		}
		else if (a > b)
		{
			y += t - s * (1 - a);
			m -= s;
		}

		ent.emplace_back(a, -2 * s);
		ent.emplace_back(b, s);
		ent.emplace_back(c, s);
	}

	sort(begin(ent), end(ent));
	ent.emplace_back(1, 0);

	T t = 0, ans = y;
	for (auto [tt, dm] : ent)
	{
		y += (tt - t) * m;
		ans = max(ans, y);
		t = tt;
		m += dm;
	}

	cout << fixed << setprecision(7) << ans;
}