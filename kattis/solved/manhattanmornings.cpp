#include <bits/stdc++.h>

using namespace std;

struct Tree
{
	typedef int		   T;
	static constexpr T unit = 0;

	T f(T a, T b)
	{
		return max(a, b);
	}

	vector<T> s;
	int		  n;

	Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val)
	{
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e)
	{
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2)
		{
			if (b % 2)
				ra = f(ra, s[b++]);
			if (e % 2)
				rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	int xh, yh, xw, yw;
	cin >> xh >> yh >> xw >> yw;
	bool					fx = xh > xw, fy = yh > yw;
	unordered_map<int, int> XCC, YCC;
	vector<pair<int, int>>	pts;

	{
		int		 iw = abs(xh - xw), ih = abs(yh - yw);
		set<int> XS, YS;
		for (int i = 0; i < n; i++)
		{
			int x, y;
			cin >> x >> y;
			x = fx ? xh - x : x - xh;
			y = fy ? yh - y : y - yh;
			if (x < 0 || x > iw || y < 0 || y > ih)
				continue;
			pts.emplace_back(x, y);
			XS.insert(x);
			YS.insert(y);
		}
		pts.emplace_back(0, 0);
		pts.emplace_back(iw, ih);
		XS.insert(0);
		YS.insert(0);
		XS.insert(iw);
		YS.insert(ih);
		for (int x : XS)
			XCC.try_emplace(x, XCC.size());
		for (int y : YS)
			YCC.try_emplace(y, YCC.size());
	}

	for (auto &[x, y] : pts)
	{
		x = XCC[x];
		y = YCC[y];
	}

	int w = XCC.size(), h = YCC.size();

	Tree tr(h);

	sort(begin(pts), end(pts));
	for (auto [x, y] : pts)
		tr.update(y, 1 + tr.query(0, y + 1));

	cout << tr.query(0, h) - 2 << '\n';
}
