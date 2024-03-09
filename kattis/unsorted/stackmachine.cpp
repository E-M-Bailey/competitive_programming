#include<bits/stdc++.h>
using namespace std;

typedef __uint128_t u128;
typedef vector<u128> vu128;
typedef vector<vu128> vvu128;

int clz(u128 x)
{
	uint64_t lo = x, hi = x >> 64;
	if (lo)
		return __builtin_ctzll(lo);
	else
		return 64 + __builtin_ctzll(hi);
}

int main()
{
	int n, m, q;
	cin >> n >> m >> q;

	array<vu128, 180> I, O;
	for (int i = 0; i < 180; i++)
	{
		I[i].resize(n);
		O[i].resize(n);
	}
	for (int i = 0; i < m; i++)
	{
		int x, y, z;
		cin >> x >> y >> z;
		x--;
		y--;
		if (z > 0)
			I[z - 40][y] |= u128(1) << x;
		else
			O[40 - z][x] |= u128(1) << y;
	}

	vector<vector<bool>> G(n * n, vector<bool>(n * n));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int z = 0; z < 180; z++)
			{
				u128 pr = I[z][i] & O[z][j];
			}
		}
	}
}