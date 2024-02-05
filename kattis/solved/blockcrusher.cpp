#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int h, w;

	while (cin >> h >> w && h)
	{
		vector<vector<int>> W(h, vector<int>(w));

		for (vector<int> &WW : W)
			for (int &wt : WW)
			{
				char ch;
				cin >> ch;
				wt = ch - '0';
			}

		vector<vector<pair<int, int>>> G(h * w + 2);

		const auto idx = [&](int i, int j)
		{
			return i * w + j;
		};
		const auto addEdge = [&](int i1, int j1, int i2, int j2)
		{
			int u  = idx(i1, j1);
			int v  = idx(i2, j2);
			int wt = W[i1][j1] + W[i2][j2];
			G[u].emplace_back(v, wt);
			G[v].emplace_back(u, wt);
		};

		for (int j = 0; j < w; j++)
		{
			G[h * w].emplace_back(idx(0, j), W[0][j]);
			G[idx(h - 1, j)].emplace_back(h * w + 1, W[h - 1][j]);
		}
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				if (i)
					addEdge(i - 1, j, i, j);
				if (j)
					addEdge(i, j - 1, i, j);
				if (i && j)
					addEdge(i - 1, j - 1, i, j);
				if (i && j < w - 1)
					addEdge(i - 1, j + 1, i, j);
			}
		}

		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;

		vector<int>	 D(h * w + 2, INT_MAX);
		vector<int>	 P(h * w + 2);
		vector<bool> V(h * w + 2, false);
		PQ.emplace(0, h * w);
		D[h * w] = 0;
		while (!PQ.empty())
		{
			auto [d, u] = PQ.top();
			PQ.pop();
			if (V[u])
				continue;
			V[u] = true;
			for (auto [v, wt] : G[u])
				if (d + wt < D[v])
				{
					D[v] = d + wt;
					P[v] = u;
					PQ.emplace(d + wt, v);
				}
		}

		vector<string> GR(h, string(w, ' '));
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				GR[i][j] = char(W[i][j] + '0');

		for (int v = P[h * w + 1]; v != h * w; v = P[v])
		{
			int i = v / w, j = v % w;
			GR[i][j] = ' ';
		}

		for (const string &s : GR)
			cout << s << '\n';
		cout << '\n';
	}
}
