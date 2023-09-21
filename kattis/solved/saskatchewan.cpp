#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

const int LIM = 1e5;

struct seg
{
	int x1, y1, x2, y2;

	seg(int X1, int Y1, int X2, int Y2) :
		x1(X1),
		y1(Y1),
		x2(X2),
		y2(Y2)
	{
		if (x1 > x2)
		{
			swap(x1, x2);
			swap(y1, y2);
		}
	}

	seg(pair<int, int> p1, pair<int, int> p2) :
		seg(p1.first, p1.second, p2.first, p2.second)
	{}

	double operator()(double x) const
	{
		return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
	}

	friend bool operator<(const seg &l, const seg &r)
	{
		int lo = max(l.x1, r.x1), hi = min(l.x2, r.x2);
		double x = 0.5 * (lo + hi);
		return lo <= hi && l(x) < r(x);
	}
};

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	vector<pair<int, int>> pts;
	int X, Y;
	while (cin >> X >> Y)
		pts.emplace_back(X, Y);

	vector<seg> S;
	for (int i = 0; i < (int)pts.size(); i++)
		if (pts[i].first != pts[(i + 1) % pts.size()].first)
			S.emplace_back(pts[i], pts[(i + 1) % pts.size()]);

	int n = (int)S.size();

	vector<vector<bool>> LT(n, vector<bool>(n));
	vector<int> CT(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j)
				CT[j] += (LT[i][j] = S[i] < S[j]);

	long long ans = 0;
	vector<int> H(LIM, -1);

	for (int i = 0; i < n; i++)
	{
		int idx = -1;
		for (int j = 0; idx < 0; j++)
			if (CT[j] == 0)
				idx = j;
		for (int j = 0; j < n; j++)
			if (j != idx)
				CT[j] -= LT[idx][j];

		auto [x1, y1, x2, y2] = S[idx];
		long long dx = x2 - x1;
		long long dy = y2 - y1;
		int plo = y1, phi = y1;
		for (int x = x1, rx = 1; x < x2; x++, rx++)
		{
			int lo = int((rx * dy + y1 * dx) / dx);
			int hi = int((rx * dy + (y1 + 1) * dx - 1) / dx);
			if (H[x] < 0)
				H[x] = max(phi, hi);
			else
			{
				int del = min(plo, lo) - H[x];
				if (del > 0)
					ans += del;
				H[x] = -1;
			}
			plo = lo;
			phi = hi;
		}
		CT[idx] = -1;
	}

	cout << ans;
}
