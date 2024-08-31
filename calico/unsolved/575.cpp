#include <bits/stdc++.h>

using namespace std;

int constexpr UNUS = 4;
int constexpr BOTH = 3;
int constexpr HORI = 2;
int constexpr VERT = 1;
int constexpr NONE = 0;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n, m;
		cin >> n >> m;
		vector<string> GR(n);
		for (auto &row : GR)
			cin >> row;

		int N = n * m * 5;

		vector<pair<int, bool>> adj;

		auto const				G = [&adj, n, m, &GR](int u)
		{
			int s = u % 5;
			int j = u / 5 % m;
			int i = u / 5 / m;

			int	 v = ((i + 1) * m + j) * 5, w = (i * m + (j + 1)) * 5;
			u -= s;
			bool wt = GR[i][j] == 'D';

			adj.clear();
			if (s == UNUS)
				adj.emplace_back(u + BOTH, 0);
			if (s == BOTH)
				adj.emplace_back(u + HORI, 0);
			if (s == BOTH)
				adj.emplace_back(u + VERT, 0);
			if (s == HORI)
				adj.emplace_back(u + NONE, 0);
			if (s == VERT)
				adj.emplace_back(u + NONE, 0);
			if (i < n - 1)
			{
				if (s == UNUS)
					adj.emplace_back(v + BOTH, wt);
				if (s == BOTH)
					adj.emplace_back(v + VERT, wt);
				if (s == VERT)
					adj.emplace_back(v + VERT, wt);
				if (GR[i + 1][j] != 'L')
				{
					if (s == UNUS)
						adj.emplace_back(v + UNUS, wt);
					if (s == HORI)
						adj.emplace_back(v + NONE, wt);
					if (s == NONE)
						adj.emplace_back(v + NONE, wt);
				}
			}
			if (j < m - 1)
			{
				if (s == UNUS)
					adj.emplace_back(w + BOTH, wt);
				if (s == BOTH)
					adj.emplace_back(w + HORI, wt);
				if (s == HORI)
					adj.emplace_back(w + HORI, wt);
				if (GR[i][j + 1] != 'L')
				{
					if (s == UNUS)
						adj.emplace_back(w + UNUS, wt);
					if (s == VERT)
						adj.emplace_back(w + NONE, wt);
					if (s == NONE)
						adj.emplace_back(w + NONE, wt);
				}
			}
		};

		// vector<vector<pair<int, int>>> G(N);
		// for (int i = 0; i < n; i++)
		// 	for (int j = 0; j < m; j++)
		// 	{
		// 		int wt = GR[i][j] == 'D';
		// 		int u = (i * m + j) * 5, v = ((i + 1) * m + j) * 5, w = (i * m + (j + 1)) * 5;
		// 		G[u + UNUS].emplace_back(u + BOTH, 0);
		// 		G[u + BOTH].emplace_back(u + HORI, 0);
		// 		G[u + BOTH].emplace_back(u + VERT, 0);
		// 		G[u + HORI].emplace_back(u + NONE, 0);
		// 		G[u + VERT].emplace_back(u + NONE, 0);
		// 		if (i < n - 1)
		// 		{
		// 			G[u + UNUS].emplace_back(v + BOTH, wt);
		// 			G[u + BOTH].emplace_back(v + VERT, wt);
		// 			G[u + VERT].emplace_back(v + VERT, wt);
		// 			if (GR[i + 1][j] != 'L')
		// 			{
		// 				G[u + UNUS].emplace_back(v + UNUS, wt);
		// 				G[u + HORI].emplace_back(v + NONE, wt);
		// 				G[u + NONE].emplace_back(v + NONE, wt);
		// 			}
		// 		}
		// 		if (j < m - 1)
		// 		{
		// 			G[u + UNUS].emplace_back(w + BOTH, wt);
		// 			G[u + BOTH].emplace_back(w + HORI, wt);
		// 			G[u + HORI].emplace_back(w + HORI, wt);
		// 			if (GR[i][j + 1] != 'L')
		// 			{
		// 				G[u + UNUS].emplace_back(w + UNUS, wt);
		// 				G[u + VERT].emplace_back(w + NONE, wt);
		// 				G[u + NONE].emplace_back(w + NONE, wt);
		// 			}
		// 		}
		// 	}

		vector<int16_t> C(N, -1);
		C[UNUS] = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				for (int s = 5; s-- > 0;)
				{
					int v = (i * m + j) * 5 + s;
					if (C[v] < 0)
						continue;
					G(v);
					for (auto [w, wt] : adj)
						C[w] = max(C[w], short(C[v] + wt));
				}

		// for (int i = 0; i < n; i++)
		// 	for (int j = 0; j < m; j++)
		// 		for (int s = 0; s < 5; s++)
		// 			cerr << ' ' << i << ' ' << j << ' ' << s << ' ' << C[(i * m + j) * 5 + s] << endl;

		// for (int s = 0; s < 5; s++)
		// {
		// 	for (int i = 0; i < n; i++)
		// 	{
		// 		cerr << ' ';
		// 		for (int j = 0; j < m; j++)
		// 			cerr << (vis[(i * m + j) * 5 + s] ? char(C[(i * m + j) * 5 + s] + '0') : '.');
		// 		cerr << endl;
		// 	}
		// 	cerr << endl;
		// }

		if (C[N - 5] >= 0)
			cout << (GR.back().back() == 'D') + C[N - 5] << '\n';
		else
			cout << "IMPOSSIBLE\n";
	}
}
