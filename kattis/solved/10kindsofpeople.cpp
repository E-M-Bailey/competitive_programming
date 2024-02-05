#include <bits/stdc++.h>

using namespace std;

pair<int, int> constexpr DIR[]{
	{1, 0},
	{0, 1},
	{0, -1},
	{-1, 0},
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<string> G(n);
	for (auto &row : G)
		cin >> row;

	int					   ctr = 0;
	vector<vector<int>>	   CI(n, vector<int>(m, -1));
	vector<pair<int, int>> S;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			if (CI[i][j] >= 0)
				continue;
			S.emplace_back(i, j);
			CI[i][j] = ctr;
			char g	 = G[i][j];
			do
			{
				auto [a, b] = S.back();
				S.pop_back();
				for (auto [di, dj] : DIR)
				{
					int c = a + di, d = b + dj;
					if (c < 0 || c >= n || d < 0 || d >= m || G[c][d] != g || CI[c][d] >= 0)
						continue;
					CI[c][d] = ctr;
					S.emplace_back(c, d);
				}
			}
			while (!S.empty());
			ctr++;
		}

	int q;
	cin >> q;
	while (q--)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--;
		b--;
		c--;
		d--;
		cout << (CI[a][b] != CI[c][d] ? "neither\n" : G[a][b] == '0' ? "binary\n" : "decimal\n");
	}
}
