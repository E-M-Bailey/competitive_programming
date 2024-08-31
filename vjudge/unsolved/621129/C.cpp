#include <bits/stdc++.h>

using namespace std;

int n;
int G[10][10], B[10][10], L[10][10][10][10], T[10][10][10][10], DP[10][10][10][10][10][10];

int dot(int i1, int j1, int i2, int j2)
{
	return i1 * i2 + j1 * j2;
}
int crs(int i1, int j1, int i2, int j2)
{
	return i1 * j2 - i2 * j1;
}

int dp(int i1, int j1, int i2, int j2, int i3, int j3)
{
	int &ans = DP[i1][j1][i2][j2][i3][j3];
	if (ans != INT_MIN)
		return ans;
	if (i1 == i2 && i1 == i3 && j1 == j2 && j1 == j3)
		return ans =
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				char c;
				cin >> c;
				G[i][j] = c == '0' ? -1 : 1;
			}
		for (int i1 = 0; i1 < n; i1++)
			for (int j1 = 0; j1 < n; j1++)
			{
				B[i1][j1] = 0;
				for (int i2 = 0; i2 <= i1; i2++)
					B[i1][j1] += G[i2][j1];
			}
		for (int i1 = 0; i1 < n; i1++)
			for (int j1 = 0; j1 < n; j1++)
				for (int i2 = 0; i2 < n; i2++)
					for (int j2 = 0; j2 < n; j2++)
					{
						if (i1 == i2 && j1 == j2)
							continue;
						int di = i2 - i1, dj = j2 - j1;
						int g = gcd(di, dj);
						di /= g;
						dj /= g;
						for (int k = 0; k <= g; k++)
							L[i1][j1][i2][j2] += 2 * G[i1 + di * k][j1 + dj * k];
						L[i1][j1][i2][j2] -= G[i1][j1] + G[i2][j2];
					}
		for (int i1 = 0; i1 < n; i1++)
			for (int j1 = 0; j1 < n; j1++)
				for (int i2 = 0; i2 < n; i2++)
					for (int j2 = 0; j2 < n; j2++)
					{
						int c12 = crs(i1, j1, i2, j2);
						if (c12 > 0)
						{
							T[i1][j1][i2][j2] = 0;
							for (int i = 0; i < n; i++)
								for (int j = 0; j < n; j++)
									if (crs(i1, j1, i, j) >= 0 && crs(i, j, i2, j2) >= 0 &&
										crs(i2 - i1, j2 - j1, i - i1, j - j1) >= 0)
										T[i1][j1][i2][j2] += G[i][j];
							T[i2][j2][i1][j1] = L[i1][j1][i2][j2] - T[i1][j1][i2][j2]
						}
						else if (dot(i1, j1, i1, j1) <= dot(i2, j2, i2, j2))
							T[i1][j1][i2][j2] = L[i1][j1][i2][j2];
					}
		for (int i1 = 0; i1 < n; i1++)
			for (int j1 = 0; j1 < n; j1++)
				for (int i2 = 0; i2 < n; i2++)
					for (int j2 = 0; j2 < n; j2++)
						for (int i3 = 0; i3 < n; i3++)
							for (int j3 = 0; j3 < n; j3++)
								for (int i1 = 0; i1 < n; i1++)
									for (int j1 = 0; j1 < n; j1++)
										for (int i2 = 0; i2 < n; i2++)
											for (int j2 = 0; j2 < n; j2++)
												for (int i3 = 0; i3 < n; i3++)
													for (int j3 = 0; j3 < n; j3++)
														DP[i1][j1][i2][j2][i3][j3] = INT_MIN;
		for (int i1 = 0; i1 < n; i1++)
			for (int j1 = 0; j1 < n; j1++)
				DP[i1][j1][i1][j1][i1][j1] = 0;
	}
}