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
	int n, d;
	cin >> n >> d;
	map<int, map<int, int>> X, Y;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		tie(x, y) = pair{x + y, x - y};
		X[y].emplace(x, i + 1);
		Y[x].emplace(y, i + 1);
	}

	for (auto const &[y, XX] : X)
		for (auto [x, i] : XX)
		{
			auto it = XX.find(x + d);
			if (it != end(XX))
			{
				int	 j	= it->second;
				auto jt = X[y - d].lower_bound(x);
				if (jt != end(X[y - d]) && jt->first <= x + d)
				{
					cout << i << ' ' << j << ' ' << jt->second << '\n';
					return;
				}
				jt = X[y + d].lower_bound(x);
				if (jt != end(X[y + d]) && jt->first <= x + d)
				{
					cout << i << ' ' << j << ' ' << jt->second << '\n';
					return;
				}
			}
		}
		
	for (auto const &[y, YY] : Y)
		for (auto [x, i] : YY)
		{
			auto it = YY.find(x + d);
			if (it != end(YY))
			{
				int	 j	= it->second;
				auto jt = Y[y - d].lower_bound(x);
				if (jt != end(Y[y - d]) && jt->first <= x + d)
				{
					cout << i << ' ' << j << ' ' << jt->second << '\n';
					return;
				}
				jt = Y[y + d].lower_bound(x);
				if (jt != end(Y[y + d]) && jt->first <= x + d)
				{
					cout << i << ' ' << j << ' ' << jt->second << '\n';
					return;
				}
			}
		}
	
	cout << "0 0 0\n";
}
