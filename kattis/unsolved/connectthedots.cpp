#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<string> G;
	string s;
	pair<int, int> M[63];
	while (cin)
	{
		G.clear();
		while (getline(cin, s) && !s.empty())
		{
			G.push_back(s);
		}

		fill(begin(M), end(M), pair{ -1, -1 });
		int n = (int)G.size(), m = (int)G[0].size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				char g = G[i][j];
				if ('0' <= g && g <= '9')
					M[g - '0'] = { i, j };
				else if ('a' <= g && g <= 'z')
					M[g - 'a' + 10] = { i, j };
				else if ('A' <= g && g <= 'Z')
					M[g - 'A' + 36] = { i, j };
			}

		for (int i = 0; M[i + 1].first >= 0; i++)
		{
			if (M[i].first == M[i + 1].first)
				for (int j = min(M[i].second, M[i + 1].second); j < max(M[i].second, M[i + 1].second); j++)
				{
					if (G[M[i].first][j] == '.')
						G[M[i].first][j] = '-';
					else if (G[M[i].first][j] == '|')
						G[M[i].first][j] = '+';
				}
			else
				for (int j = min(M[i].first, M[i + 1].first); j < max(M[i].first, M[i + 1].first); j++)
				{
					if (G[j][M[i].second] == '.')
						G[j][M[i].second] = '|';
					else if (G[j][M[i].second] == '-')
						G[j][M[i].second] = '+';
				}
		}

		for (string const &ln : G)
			cout << ln << '\n';
		cout << '\n';
	}
}