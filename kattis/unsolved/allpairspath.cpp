#include <bits/stdc++.h>

using namespace std;

int n, m, q;
int A[150][150];

bool vis[150];

int main()
{
	while (cin >> n >> m >> q, n)
	{
		for (int i = 0; i < n; ++i)
		{
			A[i][i] = 0;
			for (int j = 0; j < i; ++j)
				A[i][j] = A[j][i] = INT_MAX / 2;
		}

		while (m--)
		{
			int u, v, w;
			cin >> u >> v >> w;
			if (w < A[u][v])
				A[u][v] = w;
		}


		cout << '\n';
	}
}