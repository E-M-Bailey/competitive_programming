#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int w, h, n;
		cin >> w >> h >> n;
		vector<string> A(h), B(h);
		int			   a = 0, b = 0;
		for (auto &row : A)
		{
			cin >> row;
			a += (int)count(begin(row), end(row), '#');
		}
		for (auto &row : B)
		{
			cin >> row;
			b += (int)count(begin(row), end(row), '#');
		}

		bool done = false;
		for (int i = 0; i < n;)
		{
			while (i < n)
			{
				i++;
				int x, y;
				cin >> x >> y;
				y = h - 1 - y;
				if (B[y][x] == '#')
				{
					B[y][x] = '_';
					if (--b == 0)
					{
						done = true;
						break;
					}
				}
				else
					break;
			}
			while (i < n)
			{
				i++;
				int x, y;
				cin >> x >> y;
				y = h - 1 - y;
				if (A[y][x] == '#')
				{
					A[y][x] = '_';
					if (--a == 0)
					{
						done = true;
						break;
					}
				}
				else
					break;
			}
			while (done && i < n)
			{
				i++;
				int x, y;
				cin >> x >> y;
			}
		}
		if (a && !b)
			cout << "player one wins\n";
		else if (b && !a)
			cout << "player two wins\n";
		else
			cout << "draw\n";
	}
}
