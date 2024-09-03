#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int k;
	cin >> k;
	k += 2;

	int n = 2 * k;
	int m = 0;
	vector<vector<int>> G(n);
	for (int i = 0; i < k; i++)
		for (int j = 0; j < i; j++)
		{
			G[i * 2].push_back(j * 2 + 1);
			G[i * 2 + 1].push_back(j * 2);
			m += 2;
		}

	cout << n << ' ' << m << ' ' << 2 << '\n';
	for (int i = 0; i < k; i++)
		cout << "1 2 ";
	cout << '\n';
	for (int i = 0; i < n; i++)
		for (int j : G[i])
			cout << j + 1 << ' ' << i + 1 << '\n';
}

