#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int64_t a, b;
	cin >> a >> b;

	vector<pair<int64_t, int64_t>> F;
	for (int64_t p = 2; p * p <= a; p++)
	{
		if (a % p == 0)
		{
			F.emplace_back(p, 1);
			while ((a /= p) % p == 0)
				F.back().second++;
		}
	}
	if (a > 1)
		F.emplace_back(a, 1);

	int				m = (int)size(F);
	vector<int>		I(m);
	vector<int64_t> PP(m, 1);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < F[i].second; j++)
			PP[i] *= F[i].first;

	int64_t d = 1;

	const auto incr = [&]() -> bool
	{
		for (int i = 0; i < m; i++)
		{
			if (++I[i] <= F[i].second)
			{
				d *= F[i].first;
				return true;
			}
			I[i] = 0;
			d /= PP[i];
		}
		return false;
	};

	int64_t ans = INT64_MAX;
	do
		ans = min(ans, abs(d - b));
	while (incr());

	cout << ans;
}
