#include <bits/stdc++.h>

using namespace std;

struct TwoSat
{
	int					N;
	vector<vector<int>> gr;
	vector<int>			values;

	TwoSat(int n = 0) : N(n), gr(2 * n) {}

	void either(int f, int j)
	{
		f = max(2 * f, -1 - 2 * f);
		j = max(2 * j, -1 - 2 * j);
		gr[f].push_back(j ^ 1);
		gr[j].push_back(f ^ 1);
	}

	vector<int> val, comp, z;
	int			time = 0;

	int dfs(int i)
	{
		int low = val[i] = ++time, x;
		z.push_back(i);
		for (int e : gr[i])
			if (!comp[e])
				low = min(low, val[e] ?: dfs(e));
		if (low == val[i])
			do
			{
				x = z.back();
				z.pop_back();
				comp[x] = low;
				if (values[x >> 1] == -1)
					values[x >> 1] = x & 1;
			}
			while (x != i);
		return val[i] = low;
	}

	bool solve()
	{
		values.assign(N, -1);
		val.assign(2 * N, 0);
		comp = val;
		for (int i = 0; i < 2 * N; i++)
			if (!comp[i])
				dfs(i);
		for (int i = 0; i < N; i++)
			if (comp[2 * i] == comp[2 * i + 1])
				return 0;
		return 1;
	}
};

int main()
{
	int n;
	cin >> n;
	vector<int>			C(n);
	vector<vector<int>> A(n, vector<int>(n - 1));
	for (int i = 0; i < n; i++)
	{
		cin >> C[i];
		for (int &a : A[i])
		{
			cin >> a;
			a--;
		}
	}

	int lo = 0, hi = n - 1;
	while (lo < hi)
	{
		int t = (lo + hi) / 2;

		TwoSat TS(n);
		for (int i = 0; i < n; i++)
			for (int j = t; j < n - 1; j++)
			{
				int k = A[i][j];
				int c = C[i], d = C[k];
				if (c == d)
				{
					TS.either(i, k);
					TS.either(~i, ~k);
				}
				else if (d == (c + 1) % 3)
					TS.either(i, ~k);
				else
					TS.either(~i, k);
			}

		if (TS.solve())
			hi = t;
		else
			lo = t + 1;
	}

	cout << lo;
}
