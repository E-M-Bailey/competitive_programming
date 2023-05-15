#include <bits/stdc++.h>

using namespace std;

const int C[4][4]
{
	{2, 2, 3, 3},
	{2, 1, 1, 3},
	{0, 1, -1, -1},
	{0, 0, -1, -1}
};

int f(int64_t x, int64_t y, int64_t u)
{
	if (u == 0)
		return 0;
	switch (C[y / u][x / u])
	{
	case 0:
		return 1 + f(4 * u - 1 - y, x, u / 2);
	case 1:
		return f(x - u, y - u, u / 2);
	case 2:
		return f(x, y, u / 2);
	default:
		return 3 + f(y, 4 * u - 1 - x, u / 2);
	}
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int T;
	cin >> T;
	while (T--)
	{
		int64_t x, y;
		cin >> x >> y;
		cout << f(x, y, 1ll << 60) % 4 << '\n';
	}
}