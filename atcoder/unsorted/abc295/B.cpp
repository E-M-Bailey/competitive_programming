#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<string> G(n);
	for (string& g : G)
		cin >> g;
	vector<vector<int>> B(n, vector<int>(m, -1));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (G[i][j] >= '0' && G[i][j] <= '9')
				B[i][j] = G[i][j] - '0';
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < n; k++)
				for (int l = 0; l < m; l++)
					if (abs(i - k) + abs(j - l) <= B[k][l])
						G[i][j] = '.';
	
	for (const string& g : G)
		cout << g << '\n';
}