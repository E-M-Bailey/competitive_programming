#include <bits/stdc++.h>

using namespace std;

int constexpr M = 1000000007;

// bool check(int a, int b, vector<vector<int>> &G)
// {
// 	for (int x1 = 0; x1 < a; x1++)
// 		for (int y1 = 0; y1 < b; y1++)
// 			if (G[x1][y1] >= 0)
// 				for (int x2 = x1 + 1; x2 < a; x2++)
// 					for (int y2 = y1 + 1; y2 < b; y2++)
// 						if (G[x2][y2] >= 0 && G[x1][y2] >= 0 && G[x2][y1] >= 0 &&
// 							((G[x1][y1] == G[x1][y2] && G[x2][y1] == G[x2][y2]) ||
// 							 (G[x1][y1] == G[x2][y1] && G[x1][y2] == G[x2][y2])))
// 							return false;
// 	return true;
// }

// int solve(int a, int b, int i, int j, vector<vector<int>> &G)
// {
// 	if (j == b && i + 1 == a)
// 	{
// 		return check(a, b, G);
// 	}
// 	else
// 	{
// 		if (j == b)
// 		{
// 			j = 0;
// 			i++;
// 		}
// 		long long ans = 0;
// 		for (int x = 0; x < 3; x++)
// 		{
// 			G[i][j] = x;
// 			if (check(a, b, G))
// 				ans += solve(a, b, i, j + 1, G);
// 		}
// 		G[i][j] = -1;
// 		return int(ans % M);
// 	}
// }
// int solve(int a, int b)
// {
// 	vector<vector<int>> G(a, vector<int>(b, -1));
// 	return solve(a, b, 0, 0, G);
// }

long long mpow(long long a, long long b)
{
	long long ans = 1;
	for (; b; a = a * a % M, b = b / 2)
		if (b % 2)
			ans = ans * a % M;
	return ans;
}

int ANS[7][7]{
	{3, 9, 27, 81, 243, 729, 2187},
	{9, 66, 390, 1800, 6120, 13680, 15120},
	{27, 390, 3198, 13176, 27000, 13680, 15120},
	{81, 1800, 13176, 24336, 4320, 0, 0},
	{243, 6120, 27000, 4320, 4320, 0, 0},
	{729, 13680, 13680, 0, 0, 0, 0},
	{2187, 15120, 15120, 0, 0, 0, 0},
};

int main()
{
	// for (int i = 1; i < 4; i++)
	// {
	// 	for (int j = 1; j < 9; j++)
	// 	{
	// 		cout << solve(i, j) << ' ' << flush;
	// 	}
	// 	cout << endl;
	// }
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n, m;
		cin >> n >> m;
		if (n < m)
			swap(n, m);

		long long ans = mpow(3, (long long)n * m);
		if (m == 1)
			cout << "0\n";
		else if (n > 7)
			cout << ans << '\n';
		else
			cout << ((ans - ANS[m - 1][n - 1]) % M + M) % M << '\n';
	}
}
