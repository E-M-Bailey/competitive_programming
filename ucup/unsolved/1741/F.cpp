#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vector<long long> C(n);
	for (auto &c : C)
		cin >> c;

	vector<vector<long long>> D(n, vector<long long>(n));
	vector<vector<bool>> V(n, vector<bool>(n));

	vector<vector<pair<int, long long>>> G;
	priority_queue<pair<long long, int>> PQ;

	for (int s = 2; s <= n; s++)
	{
		G.assign(n + 1 - s, {});
		for (int l = 0, r = s - 1; r < n; l++, r++)
		{
			D[l][r] = LLONG_MAX / 2;
			for (int a = 0; a < n; a++)
			{
				int	 r2 = 2 * a - l, l2 = 2 * a - r;
				bool gr = r2 >= 0 && r2 < n, gl = l2 >= 0 && l2 < n;
				if (gr && !gl)
				{
					int m2 = 0, m = 2 * a - m2;
					D[l][r] = min(D[l][r], C[a] + max(D[m2][r2], D[m + 1][r]));
				}
				else if (!gr && gl)
				{
					int m2 = n, m = 2 * a - m2;
					D[l][r] = min(D[l][r], C[a] + max(D[l2][m2 - 1], D[l][m]));
				}
				else if (gr && gl)
					G[l2].emplace_back(l, C[a]);
			}
		}

		for (int l = 0; l + s <= n; l++)
		{
			PQ.emplace(-D[l][l + s - 1], l);
		}
		while (!PQ.empty())
		{
			auto [d, v] = PQ.top();
			PQ.pop();
			d = -d;
			if (V[v][v + s - 1])
				continue;
			V[v][v + s - 1] = true;

			for (auto [w, c] : G[v])
				if (!V[w][w + s - 1] && D[w][w + s - 1] > d + c)
				{
					PQ.emplace(-(d + c), w);
					D[w][w + s - 1] = d + c;
				}
		}
	}

	cout << D[0][n - 1];
}
