#include <bits/stdc++.h>

using namespace std;

mt19937_64					  randy(12039801);
uniform_int_distribution<int> distr(-1000, 1000);

int main()
{
	int T, B;
	cin >> T >> B;
	int T3 = T * (T - 1) * (T - 2) / 6;
	for (int a = 0; a < T; a++)
		for (int b = 0; b < T - a; b++)
			for (int c = 0; c < T - a - b; c++)
			{
				int d = T - a - b - c;
				if (B == T3 - (a * b * c + a * b * d + a * c * d + b * c * d))
				{
					vector<pair<int, int>> P;
					while ((int)P.size() < T)
					{
						int	 x = distr(randy), y = distr(randy);
						int &e = x % 2 ? (y % 2 ? d : c) : (y % 2 ? b : a);
						if (e == 0)
							continue;
						bool col = false;
						for (int i = 0; !col && i < (int)P.size(); i++)
							for (int j = i + 1; !col && j < (int)P.size(); j++)
							{
								auto [x1, y1] = P[i];
								auto [x2, y2] = P[j];
								col			  = (x1 - x) * (y2 - y) == (x2 - x) * (y1 - y);
							}
						if (!col)
						{
							P.emplace_back(x, y);
							e--;
							cout << x << ' ' << y << '\n';
						}
					}
					return 0;
				}
			}
	cout << "IMPOSSIBLE";
}
