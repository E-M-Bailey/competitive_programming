#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int m, n;
	cin >> m;
	vector<ai32<4>> R;
	vector<ai32<3>> C;
	str s;
	while (m--)
	{
		cin >> s;
		if (s[0] == 'r')
		{
			auto &[x1, y1, x2, y2] = R.emplace_back();
			cin >> x1 >> y1 >> x2 >> y2;
		}
		else
		{
			auto &[x, y, r2] = C.emplace_back();
			cin >> x >> y >> r2;
			r2 *= r2;
		}
	}
	cin >> n;
	while (n--)
	{
		int x, y, k = 0;
		cin >> x >> y;
		for (auto [x1, y1, x2, y2] : R)
			k += x1 <= x && x <= x2 && y1 <= y && y <= y2;
		for (auto [xx, yy, r2] : C)
		{
			int dx = x - xx, dy = y - yy;
			k += dx * dx + dy * dy <= r2;
		}
		cout << k << '\n';
	}
}
