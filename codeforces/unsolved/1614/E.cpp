#pragma GCC optimize("O3")

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
	// cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n, ans = 0;
	cin >> n;
	vector<int>					   A;
	vector<vector<pair<int, int>>> B, C;
	while (n--)
	{
		int t, k;
		cin >> t >> k;
		A.push_back(t);
		if ((int)size(A) == 128)
		{
			B.emplace_back();
			int x = -300000, y, z;
			do
			{
				z = INT_MAX;
				y = x;
				for (int u : A)
				{
					if (y < u)
					{
						z = min(z, x + u - y);
						y++;
					}
					else if (y == u)
						z = min(z, x + 1);
					else
						y--;
				}
				if (B.back().empty() || B.back().back().second != y - x)
					B.back().emplace_back(x, y - x);
				x = z;
			}
			while (z != INT_MAX);
			A.clear();
		}
		if ((int)size(B) == 64)
		{
			C.emplace_back();
			int x = -300000, y, z;
			do
			{
				z = INT_MAX;
				y = x;
				for (auto const &BB : B)
				{
					auto it = upper_bound(begin(BB), end(BB), pair{y, INT_MAX});
					auto jt = prev(it);
					if (it != end(BB))
						z = min(z, it->first - y + x);
					y += jt->second;
				}
				if (C.back().empty() || C.back().back().second != y - x)
					C.back().emplace_back(x, y - x);
				x = z;
			}
			while (z != INT_MAX);
			B.clear();
		}
		while (k--)
		{
			int x;
			cin >> x;
			ans = (x + ans) % 1000000001;
			for (auto const &CC : C)
				ans += prev(upper_bound(begin(CC), end(CC), pair{ans, INT_MAX}))->second;
			for (auto const &BB : B)
				ans += prev(upper_bound(begin(BB), end(BB), pair{ans, INT_MAX}))->second;
			for (int u : A)
			{
				if (ans < u)
					ans++;
				else if (ans > u)
					ans--;
			}
			cout << ans << '\n';
		}
	}
}
