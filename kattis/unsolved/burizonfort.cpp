#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		ll m;
		cin >> m;

		vector<tuple<ll, ll, ll>> PF;
		int dc = 1;
		ll m2 = m;
		for (ll p = 2; p * p <= m2; p++)
		{
			if (m2 % p == 0)
			{
				ll pp = 1;
				int ct = 0;
				do
				{
					ct++;
					pp *= p;
					m2 /= p;
				} while (m2 % p == 0);
				PF.emplace_back(p, pp, ct);
				dc *= ct + 1;
			}
		}
		if (m2 > 1)
		{
			PF.emplace_back(m2, m2, 1);
		}

		vector<ll> divs;
		divs.reserve(dc);
		ll d = 1;
		do
		{
			divs.push_back(d);
			for (auto [p, pp, ct] : PF)
			{
				if (d % pp == 0)
				{
					d /= pp;
				}
				else
				{
					d *= p;
					break;
				}
			}
		} while (d != 1);

		sort(begin(divs), end(divs));

		ll sum = 0;
		bool ans = true;
		for (auto div : divs)
		{
			if (div > sum + 1)
			{
				ans = false;
				break;
			}
			else
			{
				sum += div;
			}
		}
		cout << (ans ? "Yes\n" : "No\n");
	}
}