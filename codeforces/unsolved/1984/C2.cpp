#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n;
	cin >> n;
	long long a = 0, b = 0, c = 0, d = 1;
	bool	  s = true;
	while (n--)
	{
		int x;
		cin >> x;
		auto [a2, b2] = minmax({a + x, b + x, abs(a + x), abs(b + x)});
		long long c2 = 0, d2 = 0;
		for (auto [y, ct] : {pair{a + x, c}, pair{abs(a + x), c}, pair{b + x, d}, pair{abs(b + x), d}})
		{
			if (y == a2)
				c2 += ct;
			if (y == b2)
				d2 += ct;
		}
		if ((s &= a2 >= 0))
			c2 = 0;
		tie(c, d) = pair{c2 % 998244353, d2 % 998244353};
		tie(a, b) = pair{a2, b2};
	}
	cout << d << '\n';
}
