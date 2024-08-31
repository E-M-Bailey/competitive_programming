#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, r;
	cin >> n >> m >> r;
	vector<pair<int, int>>		 C(n);
	vector<tuple<int, int, int>> L(m);
	for (auto &[x, y] : C)
		cin >> x >> y;
	for (auto &[a, b, c] : L)
		cin >> a >> b >> c;

	int reg = 1;
	for (int i = 0; i < m; i++)
	{
		auto [a, b, c] = L[i];
		reg++;
		for (int j = 0; j < i; j++)
		{
			auto [d, e, f] = L[j];
			long long det  = a * e - d * b;
			// [a b][x]   [c]
			// [d e][y] = [f]
			long long xx = e * c - b * f, yy = -d * c + a * f;
			// (xx / det)^2 + (yy / det)^2 < r^2
			reg += xx * xx + yy * yy < r * r * det * det;
		}
	}

	if (n != reg)
	{
		cout << "no";
		return 0;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			bool good = false;
			for (auto [a, b, c] : L)
			{
				int A = a * C[i].first + b * C[i].second + c;
				int B = a * C[j].first + b * C[j].second + c;
				if ((A ^ B) < 0)
				{
					good = true;
					break;
				}
			}
			if (!good)
			{
				cout << "no";
				return 0;
			}
		}
	cout << "yes";
}