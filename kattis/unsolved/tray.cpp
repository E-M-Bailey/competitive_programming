#include <bits/stdc++.h>

using namespace std;

int coord()
{
	static string s;
	cin >> s;
	int ans = 0;
	for (char c : s)
	{
		if (c == '.')
			break;
		ans = ans * 10 + c - '0';
	}
	return ans;
}

struct piece_cell
{
	int di, dj;
	bool occupied;
};

vector<piece_cell> const P[]
{
	{{0, 0, 0}},
	//{{0, 0, 1}},
	{{0, 0, 1}, {0, 1, 1}},
	{{0, 0, 1}, {-1, 0, 1}},
};

int64_t DP[15625];

int64_t f(array<int, 3> A, int const G[])
{
	int64_t &dp = DP[A[0] * 625 + A[1] * 25 + A[2]];
	if (dp >= 0)
		return dp;
	dp = 0;
	auto sit = max_element(begin(A), end(A));
	int si = *sit - 1, sj = sit - begin(A);
	for (auto const &PP : P)
	{
		array<int, 3> B = A;
		bool good = true;
		for (auto [di, dj, occ] : PP)
		{
			int i2 = si + di, j2 = sj + dj;
			good &= 0 <= j2 && j2 < 3 && 0 <= i2 && i2 < A[j2] && (!occ || (G[i2] & (1 << j2)) == 0);
			if (!good)
				break;
			B[j2] = min(B[j2], i2);
		}
		if (good)
			dp += f(B, G);
	}
	return dp;
}

/*
array<int64_t, 27> adv(array<int64_t, 27> A, int a, int b)
{
	for (int x = 0; x < 3; x++)
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
			{
				int i = x * 9 + y * 3 + z;
				if (x == 0)
				{

				}
				else if (y == 0)
				{

				}
				else if (z == 0)
				{

				}
			}
}
*/

int main()
{
	fill(begin(DP), end(DP), -1);
	DP[0] = 1;
	int m, n;
	cin >> m >> n;
	int G[m]{};
	while (n--)
	{
		int x = coord(), y = coord();
		G[x] |= 1 << y;
	}

	cout << f({ m, m, m }, G);
}