#include <bits/stdc++.h>

using namespace std;

// x0 = sqrt(y0)
// x1 = y1 / (2 x0)
// x2 = (y2 - x1 x1) / (2 x0)
// x3 = (y3 - 2 x1 x2) / (2 x0)
// x4 = (y4 - 2 x1 x3 - x2 x2) / (2 x0)
// ...

int constexpr SQRT[10]{ 0, 1, -1, -1, 2, 5, 4, -1, -1, 3 };

int main()
{
	vector<int> Y;
	for (char c; cin >> c;)
		Y.push_back(c - '0');
	int n = (int)Y.size();
	if (n % 2 == 0)
	{
		cout << -1;
		return 0;
	}
	reverse(begin(Y), end(Y));
	{
		int z = 0;
		while (z < n && Y[z] == 0)
			z++;
		if (z % 2 == 1)
		{
			cout << -1;
			return 0;
		}
		Y.erase(begin(Y), begin(Y) + z);
		n -= z;
	}
	int m = n / 2 + 1;

	vector<int> X(m);
	for (int i = 0; i < m; i++)
	{
		int d = Y[i * 2];
	}
}