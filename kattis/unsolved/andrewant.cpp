#include <bits/stdc++.h>

using namespace std;

pair<int, int> solve(vector<int> const &LX, vector<int> const &RX)
{
	if (LX.empty())
		return { -1, -1 };
	int t = LX.back(), x = 0;
	bool r = false;
	int lx, rx;
	while (true)
	{
		if (r)
		{
			int cur = x + t;
			auto it = lower_bound(begin(LX), end(LX), cur);
			if (it == LX.begin())
				break;
			lx = *--it;
			rx = x - t;
		}
		else
		{
			int cur = x - t;
			auto it = upper_bound(begin(RX), end(RX), cur);
			if (it == RX.end())
				break;
			rx = *it;
			lx = x + t;
		}
		int x2 = (rx + lx) / 2, t2 = (lx - rx) / 2;
		if (t2 < 0)
			break;
		x = x2;
		t = t2;
		r = !r;
	}
	return { LX.back(), r ? x - t : x + t };
}

int main()
{
	int l, n;
	while (cin >> l >> n)
	{
		l *= 2;
		int x = 0;
		vector<int> LX, RX;
		while (n--)
		{
			int x;
			char c;
			cin >> x >> c;
			x *= 2;
			(c == 'R' ? RX : LX).push_back(x);
		}
		sort(begin(LX), end(LX));
		sort(begin(RX), end(RX));
		auto [lv, lp] = solve(LX, RX);
		for (auto &x : LX)
			x = l - x;
		for (auto &x : RX)
			x = l - x;
		reverse(begin(LX), end(LX));
		reverse(begin(RX), end(RX));
		LX.swap(RX);
		auto [rv, rp] = solve(LX, RX);
		rp = l - rp;
		cout << "The last ant will fall down in ";
		if (rv < lv)
			cout << lv / 2 << " seconds - started at " << lp / 2 << ".\n";
		else if (rv > lv)
			cout << rv / 2 << " seconds - started at " << rp / 2 << ".\n";
		else
			cout << lv / 2 << " seconds - started at " << min(lp, rp) / 2 << " and " << max(lp, rp) / 2 << ".\n";
	}
}