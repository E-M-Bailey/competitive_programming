#include "quality.h"

#include <bits/stdc++.h>

using namespace std;

int rectangle(int R, int C, int H, int W, int Q[3001][3001])
{
	int n = R * C, m = H * W;

	int lo = 0, hi = n;
	while (lo < hi)
	{
		int x = (lo + hi) / 2;
		vector<vector<int>> P(R + 1, vector<int>(C + 1));
		for (int i = 0; i < R; i++)
		{
			int ps = 0;
			for (int j = 0; j < C; j++)
			{
				ps += Q[i][j] <= x;
				P[i + 1][j + 1] = P[i][j + 1] + ps;
			}
		}

		bool fnd = false;
		for (int i = H; !fnd && i <= R; i++)
			for (int j = W; !fnd && j <= C; j++)
				fnd = P[i][j] - P[i - H][j] - P[i][j - W] + P[i - H][j - W] >= (m + 1) / 2;
		if (fnd)
			hi = x;
		else
			lo = x + 1;
	}
	return lo;
}

/*
int Q[3001][3001];
int main()
{
	Q[0][0] = 5;
	Q[0][1] = 11;
	Q[0][2] = 12;
	Q[0][3] = 16;
	Q[0][4] = 25;
	Q[1][0] = 17;
	Q[1][1] = 18;
	Q[1][2] = 2;
	Q[1][3] = 7;
	Q[1][4] = 10;
	Q[2][0] = 4;
	Q[2][1] = 23;
	Q[2][2] = 20;
	Q[2][3] = 3;
	Q[2][4] = 1;
	Q[3][0] = 24;
	Q[3][1] = 21;
	Q[3][2] = 19;
	Q[3][3] = 14;
	Q[3][4] = 9;
	Q[4][0] = 6;
	Q[4][1] = 22;
	Q[4][2] = 8;
	Q[4][3] = 13;
	Q[4][4] = 15;
	cout << rectangle(5, 5, 3, 3, Q);
}
*/