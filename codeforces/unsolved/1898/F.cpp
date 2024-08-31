#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int tc;
	cin >> tc;
	while (tc--)
	{
		int n, m;
		cin >> n >> m;
		vector<string> grid(n);
		vector<int>	   T;
		int			   s;
		for (int i = 0; i < n; i++)
		{
			cin >> grid[i];
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 'V')
				{
					s		   = i * m + j;
					grid[i][j] = '.';
				}
			}
		}
		for (int i = 1; i < n - 1; i++)
		{
			if (grid[i][0] == '.')
				T.push_back(i * m);
			if (grid[i][m - 1] == '.')
				T.push_back(i * m + m - 1);
		}
		for (int j = 1; j < m - 1; j++)
		{
			if (grid[0][j] == '.')
				T.push_back(j);
			if (grid[n - 1][j] == '.')
				T.push_back((n - 1) * m + j);
		}

		vector<vector<int>> G(n * m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (grid[i][j] == '.')
					for (auto [di, dj] : {pair{0, 1}, pair{0, -1}, pair{1, 0}, pair{-1, 0}})
					{
						int i2 = i + di, j2 = j + dj;
						if (i2 >= 0 && i2 < n && j2 >= 0 && j2 < m && grid[i2][j2] == '.')
							G[i * m + j].push_back(i2 * m + j2);
					}

		vector<int> DS(n * m, -1);
		queue<int>	Q;
		DS[s] = 0;
		Q.push(s);
		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for (int w : G[v])
				if (DS[w] < 0)
				{
					DS[w] = DS[v] + 1;
					Q.push(w);
				}
		}

		int cnt = 0;
		for (int t : T)
			cnt += DS[t] >= 0;

		int ans = INT_MAX;
		if (cnt == 0)
			ans = 1;
		else if (cnt == 1)
		{
			for (int t : T)
				if (DS[t] >= 0)
					ans = min(ans, DS[t] + 1);
		}
		else
		{
			vector<int> DA(n * m, -1), DI(n * m, -1), DB(n * m, -1);
			for (int t : T)
				if (DS[t] >= 0)
				{
					DA[t] = 0;
					DI[t] = t;
					Q.push(t);
				}

			while (!Q.empty())
			{
				int v = Q.front();
				Q.pop();
				bool b = v < 0;
				if (b)
					v = ~v;
				int	 d = (b ? DB : DA)[v] + 1;
				for (int w : G[v])
				{
					if (DA[w] < 0)
					{
						DA[w] = d;
						DI[w] = DI[v];
						Q.push(w);
					}
					else if (DB[w] < 0 && (b || DI[v] != DI[w]))
					{
						DB[w] = d;
						Q.push(~w);
					}
				}
			}

			for (int i = 0; i < n * m; i++)
				if (DS[i] >= 0)
					ans = min(ans, DA[i] + DB[i] + DS[i] + 1);
		}

		int cdot = 0;
		for (auto const &row : grid)
			cdot += (int)count(begin(row), end(row), '.');
		cout << cdot - ans << '\n';
	}
}
