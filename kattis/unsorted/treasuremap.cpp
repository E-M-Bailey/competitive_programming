#include <bits/stdc++.h>
using namespace std;

typedef long double ldf;

const ldf PI = atanl(1) * 4;

array<const char*, 32> HN{
	"EbS", "ESE", "SEbE", "SE", "SEbS", "SSE", "SbE", "S", "SbW", "SSW", "SWbS", "SW", "SWbW", "WSW", "WbS", "W", "WbN", "WNW", "NWbW", "NW", "NWbN", "NNW", "NbW", "N", "NbE", "NNE", "NEbN", "NE", "NEbE", "ENE", "EbN", "E"
};

int main()
{
	reverse(begin(HN), end(HN));
	unordered_map<string, pair<ldf, ldf>> H;
	for (int i = 0; i < 32; i++)
	{
		H[HN[i]] = { cosl(PI / 16 * i), sinl(PI / 16 * i) };
		//cerr << H[HN[i]].first << endl;
	}
	int n;
	while (cin >> n, n)
	{
		string h;
		ldf d;
		ldf x = 0, y = 0;
		vector<pair<ldf, ldf>> P;
		P.emplace_back(0, 0);
		for (int i = 0; i < n; i++)
		{
			cin >> h >> d;
			auto [dx, dy] = H[h];
			//cerr << "d " << dx << ' ' << dy << endl;
			x += d * dx;
			y += d * dy;
			P.emplace_back(x, y);
		}
		ldf a;
		cin >> a;
		a = -a * PI / 180;
		ldf tx = x * cosl(a) - y * sinl(a);
		ldf ty = x * sinl(a) + y * cosl(a);
		ldf ans = numeric_limits<ldf>::infinity();
		for (int i = 1; i < size(P); i++)
		{
			auto [x1, y1] = P[i - 1];
			auto [x2, y2] = P[i];
			ldf xx = tx - x1, yy = ty - y1;
			ldf dx = x2 - x1, dy = y2 - y1;
			ldf dt = dx * xx + dy * yy;
			ldf d1 = sqrtl(xx * xx + yy * yy);
			ldf xa = tx - x2, ya = ty - y2;
			ldf d2 = sqrtl(xa * xa + ya * ya);
			//cerr << ' ' << d1 << ' ' << d2;
			ans = min(ans, min(d1, d2));
			ldf m2 = (dx * dx + dy * dy);
			if (dt >= 0 && dt <= m2)
			{
				ldf ca = abs(dx * yy - dy * xx);
				//cerr << ' ' << ca;
				ans = min(ans, ca / sqrtl(m2));

			}
			//cerr << endl;
		}
		//cerr << ' ' << x << ' ' << y << endl;
		cout << fixed << setprecision(2) << ans << endl;
	}
}