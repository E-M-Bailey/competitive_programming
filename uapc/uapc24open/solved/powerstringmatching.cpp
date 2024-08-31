#include <bits/stdc++.h>

using namespace std;

int main()
{
	int	   n, m;
	string s, t;
	cin >> n >> m >> s >> t;

	vector<vector<vector<bool>>> DP(n + 1, vector<vector<bool>>(m + 1, vector<bool>(n + 1)));
	DP[0][0][0] = true;

	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
		{
			bool def	= DP[i - 1][j][0];
			bool row_or = def;
			bool mat	= true;
			for (int l = 1; l <= n; l++)
			{
				DP[i][j][l] = def;
				int i2		= i - l;
				int j2		= j - l;
				mat &= i2 >= 0 && j2 >= 0 && s[i2] == t[j2];
				if (mat)
				{
					// cerr << ' ' << i << ' ' << j << ' ' << l << ' ' << DP[i][j2][l] << endl;
					DP[i][j][l] = DP[i][j][l] || DP[i][j2][l];
				}
				row_or |= DP[i][j][l];
				// cerr << i << ' ' << j << ' ' << l << ' ' << DP[i][j][l] << endl;
			}
			// cerr << i << ' ' << j << ' ' << 0 << ' ' << row_or << endl;
			DP[i][j][0] = row_or;
		}

	cout << (DP.back().back().front() ? "yes" : "no");
}
