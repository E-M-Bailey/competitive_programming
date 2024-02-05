#include <bits/stdc++.h>

using namespace std;

struct sky
{
	int																					   n;
	unordered_map<int, unordered_map<int, unordered_map<int64_t, unordered_set<int64_t>>>> L;

	void add_seg(pair<int, int> p1, pair<int, int> p2)
	{
		if (p1 > p2)
			swap(p1, p2);
		auto [x1, y1] = p1;
		auto [x2, y2] = p2;
		int dx = x2 - x1, dy = y2 - y1;
		int g = gcd(dx, dy);
		dx /= g;
		dy /= g;
		int64_t cp	= (int64_t)dx * y1 - (int64_t)dy * x1;
		int64_t dp1 = (int64_t)dx * x1 + (int64_t)dy * y1;
		int64_t dp2 = (int64_t)dx * x2 + (int64_t)dy * y2;

		auto &LL   = L[dx];
		auto &LLL  = LL[dy];
		auto &LLLL = LLL[cp];
		if (!LLLL.insert(dp1).second)
			LLLL.erase(dp1);
		if (!LLLL.insert(dp2).second)
			LLLL.erase(dp2);
		if (LLLL.empty())
			LLL.erase(cp);
		if (LLL.empty())
			LL.erase(dy);
		if (LL.empty())
			L.erase(dx);
	}

	sky()
	{
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int x1, y1, x2, y2, x3, y3;
			cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
			add_seg({x1, y1}, {x2, y2});
			add_seg({x1, y1}, {x3, y3});
			add_seg({x2, y2}, {x3, y3});
		}
	}
};

int main()
{
	sky G{}, J{};

	cout << (G.L == J.L ? "yes" : "no");
}
