#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<vector<bool>> G(n, vector<bool>(n));
	int					 total = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			char c;
			cin >> c;
			if (c == '1')
			{
				G[i][j] = true;
				total++;
			}
		}
	}

	bool row = false, col = false;
	for (int i = 0; i < n; i++)
	{
		int ones = 0;
		for (int j = 0; j < n; j++)
			ones += G[i][j];
		row |= total <= 2 * ones;
	}
	for (int j = 0; j < n; j++)
	{
		int ones = 0;
		for (int i = 0; i < n; i++)
			ones += G[i][j];
		col |= total <= 2 * ones;
	}

	if (row && col)
		cout << '+';
	else if (row)
		cout << '-';
	else
		cout << '|';
}
