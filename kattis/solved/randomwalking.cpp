#include <bits/extc++.h>

using namespace std;

int main()
{
	int k, n, e;
	while (cin >> k >> n >> e, k)
	{
		int N = 1 << n;
		vector<vector<int>> G(N);
		while (e--)
		{
			int u, v;
			cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}

		vector<vector<double>> P(k, vector<double>(N));
		fill(begin(P[0]), end(P[0]), 1. / N);

		for (int i = 1; i < k; i++)
		{
			for (int v = 0; v < N; v++)
			{
				double amt = P[i - 1][v] / (double)size(G[v]);
				for (int u : G[v])
					P[i][u] += amt;
			}
		}

		bool good = true;
		for (int i = 0; good && i < k; i++)
		{
			vector<double> Q(n);
			for (int v = 0; v < N; v++)
				for (int j = 0, bit = 1; j < n; j++, bit *= 2)
					if (bit & v)
						Q[j] += P[i][v];
			for (double q : Q)
				good &= 0.25 < q && q < 0.75;
		}

		cout << (good ? "Yes\n" : "No\n");
	}
	
}
