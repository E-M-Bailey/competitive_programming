#include <bits/stdc++.h>

using namespace std;

const pair<int, int> DIR[]{ {0, 1}, { -1, 0 }, { 0, -1 }, { 1, 0 } };

#define IDX(i, j, d) (((i) * m + (j)) * 4 + (d))

int main()
{
	int n, m, C;
	cin >> n >> m >> C;

	vector<vector<array<int, 4>>> T(n, vector<array<int, 4>>(m, { 1, 3, 0, 2 }));

	int si, sj, ti, tj;
	cin >> si >> sj >> ti >> tj;
	si--;
	sj--;
	ti--;
	tj--;

	while (C--)
	{
		int s, a, t, r, l;
		cin >> s >> a >> t >> r >> l;
		s--;
		a--;
		T[s][a] = { t, l, 0, r };
	}
	T[0][0] = { 0, 0, 0, 0 };

	int N = n * m * 4;
	vector<vector<pair<int, int>>> G(N);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int d = 0; d < 4; d++)
			{
				int idx = IDX(i, j, d);
				for (int dd = 0; dd < 4; dd++)
				{
					if (dd == 2)
						continue;
					int d2 = (dd + d) % 4;
					auto [di, dj] = DIR[d2];
					int i2 = i + di, j2 = j + dj;
					if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= m)
						continue;
					int idx2 = IDX(i2, j2, d2);
					G[idx].emplace_back(idx2, T[i][j][dd] + 1);
				}
			}

	auto dist = [&](int s, int t)
	{
		vector<int> D(N, INT_MAX / 2);
		vector<bool> V(N);
		priority_queue<pair<int, int>> PQ;
		PQ.emplace(0, s);
		D[s] = 0;
		while (!PQ.empty())
		{
			int v = PQ.top().second, d = D[v];
			PQ.pop();
			if (V[v])
				continue;
			V[v] = true;
			if (v == t)
				break;
			for (auto [w, wt] : G[v])
			{
				int dw = d + wt;
				if (dw < D[w])
				{
					D[w] = dw;
					PQ.emplace(-dw, w);
				}
			}
		}
		return D[t];
	};

	int64_t ans = LLONG_MAX;

	for (int a : array<int, 2>{IDX(0, 1, 0), IDX(1, 0, 3)})
		for (int d : array<int, 2>{IDX(0, 0, 1), IDX(0, 0, 2)})
			for (int sd = 0; sd < 4; sd++)
				for (int td = 0; td < 4; td++)
				{
					int b = IDX(si, sj, sd), c = IDX(ti, tj, td);
					int64_t d1 = dist(a, b) + 1,
						d2 = dist(b, c),
						d3 = dist(c, d);
					ans = min(ans, d1 + d2 + d3);
				}
	cout << ans;
}