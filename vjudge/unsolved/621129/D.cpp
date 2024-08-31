#include <bits/stdc++.h>

using namespace std;

typedef long long				ll;
typedef unordered_set<ll>		us;
typedef unordered_map<ll, us>	uus;
typedef unordered_map<ll, uus>	uuus;
typedef unordered_map<ll, uuus> uuuus;
typedef unordered_map<ll, int>	um;
typedef unordered_map<ll, um>	uum;
typedef unordered_map<ll, uum>	uuum;
typedef unordered_map<ll, uuum> uuuum;

void in(uuuum &C)
{
	int n;
	cin >> n;
	auto const add = [&](ll x1, ll y1, ll x2, ll y2)
	{
		ll a = y2 - y1, b = x1 - x2, c = a * x1 + b * y1;
		ll g = gcd(gcd(a, b), c);
		if (a < 0 || (a == 0 && b < 0))
			g = -g;
		a /= g;
		b /= g;
		c /= g;
		C[a][b][c][b * x1 - a * y1]++;
		C[a][b][c][b * x2 - a * y2]++;
	};
	while (n--)
	{
		ll x1, y1, x2, y2, x3, y3;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		add(x1, y1, x2, y2);
		add(x2, y2, x3, y3);
		add(x3, y3, x1, y1);
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	uuuum C;
	in(C);
	in(C);
	for (auto const &[a, CC] : C)
		for (auto const &[b, CCC] : CC)
			for (auto const &[c, CCCC] : CCC)
				for (auto [d, f] : CCCC)
					if (f % 2)
					{
						cout << "no";
						return 0;
					}
	cout << "yes";
}
