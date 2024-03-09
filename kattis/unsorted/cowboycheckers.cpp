#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	char G[49];
	for (char &g : G)
		cin >> g;

	char S[24]
	{
		G[0],
		G[3],
		G[6],
		G[8],
		G[10],
		G[12],
		G[16],
		G[17],
		G[18],
		G[21],
		G[22],
		G[23],
		G[25],
		G[26],
		G[27],
		G[30],
		G[31],
		G[32],
		G[36],
		G[38],
		G[40],
		G[42],
		G[45],
		G[48]
	};

	int const H[8][3]
	{
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{9, 10, 11},
		{12, 13, 14},
		{15, 16, 17},
		{18, 19, 20},
		{21, 22, 23}
	};
	int const V[8][3]
	{
		{0, 9, 21},
		{3, 10, 18},
		{6, 11, 15},
		{1, 4, 7},
		{16, 19, 22},
		{8, 12, 17},
		{5, 13, 20},
		{2, 14, 23}
	};

	bool A[24][24]{};
	for (int i = 0; i < 8; i++)
		A[V[i][0]][V[i][1]] = A[V[i][1]][V[i][0]] = A[V[i][1]][V[i][2]] = A[V[i][2]][V[i][1]] = A[H[i][0]][H[i][1]] = A[H[i][1]][H[i][0]] = A[H[i][1]][H[i][2]] = A[H[i][2]][H[i][1]] = true;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i == j)
				continue;
			for (int mask = 0; mask < 4; mask++)
			{
				int const *X = (mask & 1 ? H : V)[i], *Y = (mask & 2 ? H : V)[j];
				bool good = true;
				int idx = -1;
				for (int k = 0; good && k < 3; k++)
				{
					good &= S[X[k]] == 'W';
					if (S[Y[k]] != 'W')
					{
						good &= S[Y[k]] == '.' && idx == -1;
						idx = Y[k];
					}
				}
				good &= idx != -1;
				if (!good)
					continue;
				good = false;
				for (int k = 0; !good && k < 3; k++)
				{
					good |= A[X[k]][idx];
					for (int l = 0; l < 3; l++)
						good &= X[k] != Y[l];
				}
				if (good)
				{
					//cerr << i << ' ' << j << ' ' << mask << endl;
					cout << "double mill";
					return 0;
				}
			}
		}
	cout << "no double mill";
}