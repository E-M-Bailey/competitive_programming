#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<pair<long double, long double>> B(n);
	for (auto &[s, p] : B)
		cin >> s >> p;
	B.emplace_back(numeric_limits<long double>::infinity(), 0);
	cin >> B.back().second;
	int k;
	cin >> k;
	while (k--)
	{
		long double e, m;
		cin >> e >> m;
		int i = 0;
		long double rem = B[0].first;
		for (;;)
		{
			if (rem <= e)
			{
				e -= rem;
				rem = B[++i].first;
			}
			else
			{
				rem -= e;
				break;
			}
		}
		long double ans = 0;
		for (;;)
		{
			long double p = 1 - B[i].second / 100;
			if (rem * p <= m)
			{
				m -= rem * p;
				ans += rem;
				rem = B[++i].first;
			}
			else
			{
				ans += m / p;
				break;
			}
		}
		cout << fixed << setprecision(8) << ans << '\n';
	}
}
