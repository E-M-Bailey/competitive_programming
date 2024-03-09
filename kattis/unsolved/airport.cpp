#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<pair<int, int>> P(n);
	for (auto &[x, y] : P)
		cin >> x >> y;

	vector<pair<long long, long long>> P2(n);
	for (int i = 0; i < n; i++)
	{
		auto [x1, y1] = P[i];
		for (int j = i + 1; j < n; j++)
		{
			auto [x2, y2] = P[j];
			int64_t dx2 = x2 - x1, dy2 = y2 - y1;
			for (int k = 0; k < n; k++)
			{
				auto [x3, y3] = P[k];
				int64_t dx3 = x3 - x1, dy3 = y3 - y1;
				P2[k].first = dx2 * dx3 + dy2 * dy3;
				P2[k].second = dx2 * dy3 - dy2 * dx3;
			}
			D.clear();
			int s = -1;
			for (int k = 1; k < n; k++)
			{
				if (s * P[(k + i) % n].second < 0)
				{
					s = -s;
					auto [x1, y1] = P2[i]
				}
			}

		}
	}
}