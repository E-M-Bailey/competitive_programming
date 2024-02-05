#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	int64_t									 b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
	vector<tuple<int64_t, int64_t, int64_t>> X(n);
	for (auto &[x, y, z] : X)
	{
		cin >> x >> y >> z;
		b = max(b, x);
		c = max(c, y);
		d = max(d, z);
		e = max(e, x + y);
		f = max(f, x + z);
		g = max(g, y + z);
		h = max(h, x + y + z);
	}

	int64_t bestoc = LLONG_MAX;
	int		besti  = -1;
	for (int i = 0; i < n; i++)
	{
		auto [x, y, z] = X[i];
		int64_t oc	   = max({(int64_t)0, b - x, c - y, d - z, e - (x + y), f - (x + z), g - (y + z), h - (x + y + z)});
		if (oc < bestoc)
		{
			bestoc = oc;
			besti  = i;
		}
	}
	cout << bestoc << ' ' << besti + 1;
}
