#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	a--;
	b--;

	vector<vector<int>> G(n);
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
	}

	vector<vector<int>> D(n, vector<int>(n, -1));
	queue<int>			Q;
	for (int s = 0; s < n; s++)
	{
		D[s][s] = 0;
		Q.push(s);
		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for (int w : G[v])
				if (D[s][w] < 0)
				{
					D[s][w] = D[s][v] + 1;
					Q.push(w);
				}
		}
	}

	int							   N = n * n;
	vector<vector<pair<int, int>>> H(2 * N + n);
	// H[s * n + t]: at s going to t
	// H[N + s * n + t]: at s going to t, can get off train
	// H[2 * N + s]: at s not on a train
	for (int s = 0; s < n; s++)
	{
		int off_s = 2 * N + s;
		for (int t = 0; t < n; t++)
		{
			int on2_s = s * n + t, on1_s = N + on2_s;
			H[on1_s].emplace_back(on2_s, 0);
			H[on1_s].emplace_back(off_s, 0);
			for (int v : G[s])
			{
				int on1_v = N + v * n + t;
				if (D[v][t] >= 0 && D[v][t] + 1 == D[s][t])
					H[on2_s].emplace_back(on1_v, 0);
			}
		}
	}

	int k;
	cin >> k;
	vector<vector<int>> L(n);
	while (k--)
	{
		int s, t;
		cin >> s >> t;
		s--;
		t--;
		if (D[s][t] < 0)
			continue;
		for (int v = 0; v < n; v++)
			if (D[s][v] >= 0 && D[v][t] >= 0 && D[s][v] + D[v][t] == D[s][t])
				L[D[s][v]].push_back(v);

		for (auto &LL : L)
		{
			if (size(LL) == 1)
				for (int v : LL)
				{
					int off_v = 2 * N + v;
					for (int w : G[v])
						if (D[w][t] >= 0 && D[w][t] + 1 == D[v][t])
						{
							int on2_v = v * n + t;
							H[off_v].emplace_back(on2_v, 1);
						}
				}
			LL.clear();
		}
	}

	vector<int>					   deg(2 * N + n);
	vector<vector<pair<int, int>>> R(2 * N + n);
	for (int x = 0; x < 2 * N + n; x++)
	{
		deg[x] = x < N ? (int)size(H[x]) : 1;
		for (auto [y, wt] : H[x])
			R[y].emplace_back(x, wt);
	}

	vector<int>			  dist(2 * N + n, -1);
	deque<pair<int, int>> DQ{{2 * N + b, 0}};
	deg[2 * N + b] = 0;
	while (!DQ.empty())
	{
		auto [v, dv] = DQ.front();
		DQ.pop_front();
		if (dist[v] >= 0)
			continue;
		dist[v] = dv;
		for (auto [w, wt] : R[v])
			if (dist[w] < 0 && --deg[w] <= 0)
			{
				if (wt)
					DQ.emplace_back(w, dv + 1);
				else
					DQ.emplace_front(w, dv);
			}
	}

	cout << dist[2 * N + a];
}
