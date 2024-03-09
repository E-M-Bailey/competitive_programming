#include <bits/stdc++.h>

using namespace std;

typedef long double T;

int main()
{
	int n, m;
	cin >> n >> m;

	vector<T> F(n + 1);
	F[0] = 1;
	for (int i = 1; i <= n; i++)
		F[i] = F[i - 1] * i;
	vector<vector<T>> DP(n + 1, vector<T>(m + 1));
	DP[0][0] = 1;

	for (int k = 0; k <= n; k++)
		for (int s = 0; s <= m; s++)
			for (int j = 1; j <= s; j++)
				for (int c = 1; c <= k; c++)
					if (int b = s - j * k; b >= 0)
						DP[k][s] += DP[k - c][b] / F[c];

	
	for (int k = 0; k <= n; k++)
	{
		for (auto dp : DP[k]) cerr << dp << ' ';
		cerr << endl;
	}
}