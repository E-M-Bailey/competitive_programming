#include <bits/stdc++.h>

using namespace std;

struct line
{
	int a, b, c;
	long double side(long double x, long double y) const
	{
		return a * x + b * y - c;
	}
};

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int T;
	cin >> T;
	bool fst = true;
	while (T--)
	{
		if (!fst)
			cout << '\n';
		fst = false;
		int n;
		cin >> n;
		vector<line> L(n);
		array<vector<int>, 4> A;
		const auto add_pt = [&](int x, int y)
		{
			if (x == 0)
				A[0].push_back(y);
			else if (x == 200)
				A[1].push_back(y);
			else if (y == 0)
				A[2].push_back(x);
			else
				A[3].push_back(x);
		};
		for (line& l : L)
		{
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			x1 *= 2;
			y1 *= 2;
			x2 *= 2;
			y2 *= 2;
			l.a = y2 - y1;
			l.b = x1 - x2;
			l.c = l.a * x1 + l.b * y1;
			//cerr << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << a << ' ' << b << ' ' << c << ' ' << a * x2 + b * y2 << endl;
			add_pt(x1, y1);
			add_pt(x2, y2);
		}
		long double X, Y;
		cin >> X >> Y;
		X *= 2;
		Y *= 2;
		int best = INT_MAX;
		for (int i = 0; i < 4; i++)
		{
			auto& AA = A[i];
			AA.push_back(0);
			AA.push_back(200);
			sort(begin(AA), end(AA));
			AA.resize(unique(begin(AA), end(AA)) - begin(AA));
			for (int j = 1; j < (int)AA.size(); j++)
			{
				int ct = 1;
				int pos = (AA[j] + AA[j - 1]) / 2;
				int x, y;
				switch (i)
				{
				case 0:
					x = 0;
					y = pos;
					break;
				case 1:
					x = 200;
					y = pos;
					break;
				case 2:
					x = pos;
					y = 0;
					break;
				case 3:
					x = pos;
					y = 200;
					break;
				}
				for (const line& l : L)
				{
					//if (l.side(x, y) * l.side(X, Y) < 0)
					//	cerr << ' ' << l.a << ' ' << l.b << ' ' << l.c << endl;
					ct += l.side(x, y) * l.side(X, Y) < 0;
				}
				//cerr << x << ' ' << y << ' ' << ct << endl;
				best = min(best, ct);
			}
		}
		cout << "Number of doors = " << best << '\n';
	}
}