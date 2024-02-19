#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int r, c, a, b;
	cin >> r >> c >> a >> b;
	string dummy;
	getline(cin, dummy);
	vector<string> G(r);
	for (auto &row : G)
		getline(cin, row);

	for (int i = 0; i < r; i++)
		for (int k = 0; k < a; k++)
		{
			for (int j = 0; j < c; j++)
				for (int l = 0; l < b; l++)
					cout << G[i][j];
			cout << '\n';
		}
}
