#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, S;
	dso(int n) : P(n), S(n, 1)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = pair{P[x], P[P[x]]};
		return x;
	}
	void onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return;
		if (S[x] < S[y])
			swap(x, y);
		S[x] += S[y];
		P[y] = x;
	}
};

pair<int, int> const DIR[4]{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<char>> G(n, vector<char>(m));
	dso					 D(n * m);
	const auto			 add = [&](int i, int j)
	{
		G[i][j] = true;
		int a	= i * m + j;
		for (auto [di, dj] : DIR)
		{
			int i2 = i + di, j2 = j + dj;
			if (i2 < 0 || i2 >= n || j2 < 0 || j2 > m || !G[i2][j2])
				continue;
			int b = i2 * m + j2;
			D.onion(a, b);
		}
	};
	int s = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			char c;
			cin >> c;
			if (c == 'S' || c == '#')
				add(i, j);
			if (c == 'S')
				s = i * m + j;
		}
	s = D.find(s);
	cout << D.S[s] << '\n';
	for (int i = 0; i < q; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		add(a, b);
		s = D.find(s);
		cout << D.S[s] << '\n';
	}
}
