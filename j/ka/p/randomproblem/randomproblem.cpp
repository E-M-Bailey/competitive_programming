#include <bits/stdc++.h>

using namespace std;

int16_t cnt[1 << 19][10][10];
int8_t valxy[1 << 19][10][10], valxz[1 << 19][10][10], valyz[1 << 19][10][10];

int main()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	for (int a = 0; a < n; a++)
	{
		int x = A[a];
		for (int b = a + 1; b < n; b++)
		{
			int y = A[b];
			int l = b - a - 1;
			int i = 999 * l - l * (l + 1) / 2;
			for (int c = b + 1; c < n; c++)
			{
				int z = A[c];
				int r = c - b - 1;
				int j = i + r;
				if (valxy[j][x][y] == 0)
					valxy[j][x][y] = uint8_t(z + 1);
				else if (valxy[j][x][y] != z + 1)
					valxy[j][x][y] = -1;
				if (valxz[j][x][z] == 0)
					valxz[j][x][z] = uint8_t(y + 1);
				else if (valxz[j][x][z] != y + 1)
					valxz[j][x][z] = -1;
				if (valyz[j][y][z] == 0)
					valyz[j][y][z] = uint8_t(x + 1);
				else if (valyz[j][y][z] != x + 1)
					valyz[j][y][z] = -1;
				++cnt[j][x][y];
			}
		}
	}

	int lim = (n + 39) / 40;
	for (int a = 0; a < n; a++)
	{
		int x = A[a];
		for (int b = a + 1; b < n; b++)
		{
			int y = A[b];
			int l = b - a - 1;
			int i = 999 * l - l * (l + 1) / 2;
			for (int c = b + 1; c < n; c++)
			{
				int z = A[c];
				int r = c - b - 1;
				int j = i + r;
				if (cnt[j][x][y] > lim && valxy[j][x][y] >= 0 && valxz[j][x][z] >= 0 && valyz[j][y][z] >= 0)
				{
					cout << "triple correlation " << x << '(' << b - a << ')' << y << '(' << c - b << ')' << z << " found";
					return 0;
				}
			}
		}
	}
	cout << "random sequence";
}