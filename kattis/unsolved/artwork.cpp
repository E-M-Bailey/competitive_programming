#include <bits/stdc++.h>

using namespace std;

struct dso
{

	vector<int> P, R;
	dso(int n) : P(n), R(n)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = make_tuple(P[x], P[P[x]]);
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (R[x] < R[y])
			swap(x, y);
		P[y] = x;
		R[x] += R[x] == R[y];
		return true;
	}
};

pair<int, int> const dir[4]
{
	pair<int, int>(-1, 0),
	pair<int, int>(1, 0),
	pair<int, int>(0, -1),
	pair<int, int>(0, 1)
};

int main()
{
	int n, m, q;
	cin >> n >> m >> q;

	vector<vector<bool>> G(n, vector<bool>(m, true));
	vector<set<int>> R(m), C(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			C[i].insert(j);
			R[j].insert(i);
		}
	vector<vector<pair<int, int>>> Q(q);

	for (auto &QQ : Q)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1--;
		y1--;
		x2--;
		y2--;
		if (x1 == x2)
		{
			for (;;)
			{
				auto it = C[x1].lower_bound(y1);
				if (it == C[x1].end() || *it > y2)
					break;
				QQ.emplace_back(x1, *it);
				G[x1][*it] = false;
				R[*it].erase(x1);
				C[x1].erase(it);
			}
		}
		else
		{
			for (;;)
			{
				auto it = R[y1].lower_bound(x1);
				if (it == R[y1].end() || *it > x2)
					break;
				QQ.emplace_back(*it, y1);
				G[*it][y1] = false;
				C[*it].erase(y1);
				R[y1].erase(it);
			}
		}
	}

	int k = 0;
	dso D(n * m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (!G[i][j])
				continue;
			k++;
			int idx = i * m + j;
			for (auto [di, dj] : dir)
			{
				int i2 = i + di, j2 = j + dj;
				if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= m || !G[i2][j2])
					continue;
				int idx2 = i2 * m + j2;
				if (D.onion(idx, idx2))
					k--;
			}
		}
	vector<int> ans(q);

	while (q--)
	{
		ans[q] = k;

		for (auto [i, j] : Q[q])
		{
			G[i][j] = true;
			k++;
			int idx = i * m + j;
			for (auto [di, dj] : dir)
			{
				int i2 = i + di, j2 = j + dj;
				if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= m || !G[i2][j2])
					continue;
				int idx2 = i2 * m + j2;
				if (D.onion(idx, idx2))
					k--;
			}
		}
	}

	for (int a : ans)
		cout << a << '\n';
}