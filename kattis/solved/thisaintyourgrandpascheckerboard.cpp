#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<string> G(n);
	for (string &row : G)
		cin >> row;
	vector<int> C(n);
	for (int i = 0; i < n; i++)
	{
		if (count(begin(G[i]), end(G[i]), 'W') != n / 2)
		{
			cout << 0;
			return 0;
		}
		for (int j = 0; j < n; j++)
			C[j] += G[i][j] == 'W';
		for (int j = 2; j < n; j++)
		{
			if ((G[i][j - 2] == G[i][j - 1] && G[i][j - 1] == G[i][j]) || (G[j - 2][i] == G[j - 1][i] && G[j - 1][i] == G[j][i]))
			{
				cout << 0;
				return 0;
			}
		}
	}
	if (count(begin(C), end(C), n / 2) != n)
	{
		cout << 0;
		return 0;
	}
	cout << 1;
}
