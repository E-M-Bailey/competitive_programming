#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
	int n;
	cin >> n;
	vector<pair<ll, ll>> XY(n);
	for (auto &[x, y] : XY)
		cin >> x >> y;
	
	vector<int> N(n);
	for (int i = 0; i < n; i++)
		if (XY[i].second != XY[n - 1].second)
		{
			N[n - 1] = i;
			break;
		}
	for (int i = n - 1; i-- > 0;)
		if (XY[i].second == XY[i + 1].second)
			N[i] = N[i + 1];
		else
			N[i] = i + 1;

	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		int a = i - 1, b = i, c = i + 1;
		if (i == 0)
			a = n - 1;
		if (i == n - 1)
			c = 0;
		
		auto [ax, ay] = XY[a];
		auto [bx, by] = XY[b];
		auto [cx, cy] = XY[c];

		auto dx1 = bx - ax, dy1 = by - ay, dx2 = cx - bx, dy2 = cy - by;
		auto cr = dx1 * dy2 - dy1 * dx2;
		if (by < ay && by < XY[N[i]].second && cr > 0)
			ans++;
	}
	cout << ans;
}
