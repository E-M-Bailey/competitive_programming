#include <bits/stdc++.h>

using namespace std;

struct dso
{
	int			k;
	vector<int> P, S;
	dso(int n) : k(n), P(n), S(n, 1)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			x = exchange(P[x], P[P[x]]);
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (S[x] < S[y])
			swap(x, y);
		S[x] += S[y];
		P[y] = x;
		k--;
		return true;
	}
};

int main()
{
	int r, c;
	cin >> r >> c;
	vector<string> grid(r);
	for (auto &row : grid)
		cin >> row;

	int s = (r + 1) * (c + 1);
	dso D(s + 1);

	vector<vector<bool>> C(r + 1, vector<bool>(c + 1));
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
		{
			if (grid[i][j] == '/')
				C[i + 1][j] = C[i][j + 1] = true;
			else if (grid[i][j] == '\\')
				C[i][j] = C[i + 1][j + 1] = true;
		}

	auto const add = [&](int i1, int j1, int i2, int j2)
	{
		if (C[i1][j1] || C[i2][j2])
			return;
		D.onion(i1 * (c + 1) + j1, i2 * (c + 1) + j2);
	};

	for (int i = 0; i <= r; i++)
	{
		D.onion(i * (c + 1), s);
		D.onion(i * (c + 1) + c, s);
		for (int j = 0; j <= c; j++)
		{
			if (C[i][j])
				D.onion(i * (c + 1) + j, s);
		}
	}
	for (int j = 0; j <= c; j++)
	{
		D.onion(j, s);
		D.onion(r * (c + 1) + j, s);
	}

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			add(i, j, i + 1, j);
			add(i + 1, j, i + 1, j + 1);
			add(i + 1, j + 1, i, j + 1);
			add(i, j + 1, i, j);

			if (grid[i][j] != '/')
				add(i, j, i + 1, j + 1);
			if (grid[i][j] != '\\')
				add(i, j + 1, i + 1, j);
		}
	}
	cout << D.k - 1;
}
