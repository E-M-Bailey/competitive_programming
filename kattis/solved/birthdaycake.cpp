#include <bits/stdc++.h>

using namespace std;

struct candle
{
	int x, y;

	friend istream &operator>>(istream &is, candle &c)
	{
		return is >> c.x >> c.y;
	}
};

// [-a1 -b1][x]   [c1]
// [-a2 -b2][y] = [c2]
// Ax = c

const pair<long double, long double> NIL{200, 200};

struct line
{
	int a, b, c;

	friend istream &operator>>(istream &is, line &l)
	{
		return is >> l.a >> l.b >> l.c;
	}

	friend pair<long double, long double> isect(const line &l1, const line &l2)
	{
		int det = l1.a * l2.b - l1.b * l2.a;
		if (det == 0)
			return NIL;
		// neg. inv.
		long double f = 1.l / det, a = -l2.b * f, b = l1.b * f, c = l2.a * f, d = -l1.a * f;
		return {a * l1.c + b * l2.c, c * l1.c + d * l2.c};
	}

	bool side(const candle &C) const
	{
		return a * C.x + b * C.y + c > 0;
	}
};

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, m, r;
	cin >> n >> m >> r;

	vector<candle> C(n);
	for (candle &c : C)
		cin >> c;

	vector<line> L(m);
	for (line &l : L)
		cin >> l;

	int ct = m + 1;
	for (int i = 0; i < m; i++)
		for (int j = i + 1; j < m; j++)
		{
			auto [x, y] = isect(L[i], L[j]);
			ct += x * x + y * y <= r * r;
		}
	if (ct != n)
	{
		cout << "no";
		return 0;
	}

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			bool fnd = false;
			for (const line &l : L)
				if (l.side(C[i]) != l.side(C[j]))
				{
					fnd = true;
					break;
				}
			if (!fnd)
			{
				cout << "no";
				return 0;
			}
		}
	cout << "yes";
}
