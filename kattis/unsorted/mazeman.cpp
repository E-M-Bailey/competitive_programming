#include <bits/stdc++.h>

using namespace std;

pair<int, int> const DIR[]{
	pair{-1, 0},
	pair{1, 0},
	pair{0, -1},
	pair{0, 1}};

int main()
{
	int n, m;
	cin >> n >> m;
	string dummy;
	getline(cin, dummy);
	vector<string> grid(n);
	for (auto &row : grid)
		getline(cin, row);
	vector<vector<bool>> vis(n, vector<bool>(m));
	vector<pair<int, int>> S;

	int ans1 = 0, ans2 = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{	
			char g = grid[i][j];
			if ('A' <= g && g <= 'W' && !vis[i][j])
			{
				bool needed = false;
				S.emplace_back(i, j);
				vis[i][j] = true;
				while (!S.empty())
				{
					auto [a, b] = S.back();
					S.pop_back();
					for (auto const [da, db] : DIR)
					{
						int c = a + da, d = b + db;
						if (c < 0 || c >= n || d < 0 || d >= m || vis[c][d] || ('A' <= grid[c][d] && grid[c][d] <= 'X'))
							continue;
						S.emplace_back(c, d);
						vis[c][d] = true;
						needed |= grid[c][d] == '.';
					}
				}
				ans1 += needed;
			}
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans2 += grid[i][j] == '.' && !vis[i][j];
	cout << ans1 << ' ' << ans2;
}
