#include <bits/stdc++.h>

using namespace std;

const long double S2 = sqrtl(2);
const long double EPS = 5e-12l;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cout << fixed << setprecision(11);
	long double r, x, y, X, Y;
	vector<pair<const char*, long double>> C;
	while (cin >> r >> x >> y >> X >> Y)
	{
		bool ddone = false;
		bool sw = false;
		const auto diag = [&](int dy, int dx, const char* name)
		{
			long double ay = dy * (Y - y), ax = dx * (X - x);
			long double a = min(ay, ax);
			if (ddone || a <= EPS)
				return;
			//if (ay < ax)
			//{
			//	x = 
			//}
			y += a * dy;
			x += a * dx;
			long double x2 = X - a * dx, y2 = Y - a * dy;

			if (x * x + y * y >= x2 * x2 + y2 * y2)
				sw = true;
			C.emplace_back(name, a * S2);
			ddone = true;
		};

		diag(1, 1, "northeast ");
		diag(1, -1, "northwest ");
		diag(-1, 1, "southeast ");
		diag(-1, -1, "southwest ");

		if (Y > y + EPS)
			C.emplace_back("north ", Y - y);
		else if (Y < y - EPS)
			C.emplace_back("south ", y - Y);
		else if (X > x + EPS)
			C.emplace_back("east ", X - x);
		else if (X < x - EPS)
			C.emplace_back("west ", x - X);
		if (sw && C.size() > 1)
			swap(C[0], C[1]);
		for (const auto& [a, b] : C)
			cout << a << b << '\n';
		C.clear();
		cout << '\n';
	}
}