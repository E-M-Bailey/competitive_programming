#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, k;
	while (cin >> n >> m >> k, n)
	{
		vector<pair<int, int>> X;
		vector<bool> R(n), C(m), U(n + m - 1), D(n + m - 1);
		while (k--)
		{
			int x, y;
			cin >> x >> y;
			x--;
			y--;
			X.emplace_back(x, y);
			R[x]			 = true;
			C[y]			 = true;
			U[x - y + m - 1] = true;
			D[x + y]		 = true;
		}

		int ans = 0;
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				ans += !(R[i] || C[j] || U[i - j + m - 1] || D[i + j]);

		cout << ans << '\n';
	}
}