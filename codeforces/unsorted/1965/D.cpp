#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	//cin >> tc;
	while (tc--)
	{
		go();
	}
}

int n, m, k;
vector<vector<int>> grid;
vector<vector<pair<int, int>>> rep;
vector<tuple<int, int, int>> ans;

bool layer(int z)
{
	vector<int> R(m, -1), B(n, -1);
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
			if (rep[x][y] == pair{x, y})
				rep[x][y
	}
}

void go()
{
	cin >> n >> m >> k;
	grid.resize(n, vector<int>(m));
	rep.resize(n, vector<pair<int, int>>(m));
	for (int i = 0; i <n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> grid[i][j];
			rep[i][j] = {i, j};
		}
	}

	for (int z = )
}
