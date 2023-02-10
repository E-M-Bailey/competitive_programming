#include <bits/stdc++.h>
using namespace std;

constexpr int BIG = 5e8;
constexpr int MAXn = 1000;
constexpr int MAXC = 101;
constexpr int MAXN = MAXn * MAXC;
constexpr int MAXM = 10000;

int main()
{
	istream_iterator<int> in(cin);

	int n = *in++, m = *in++, N = n * MAXC;

	vector<int> P(n);
	vector<int> E(m * 3);

	copy_n(in, n, P);
	copy_n(in, m * 3, E);

	vector<vector<pair<int, int>>> G(N);
	for (int i = 0; i < n; i++)
	{
		int u = E[i], v = E[i + 1], d = E[i + 2];
		for (int j = d; j < MAXC; j++)
		{
			int a = u * MAXC + j, b = v * MAXC + j;
			G[a].emplace_back(b - d, 0);
			G[b].emplace_back(a - d, 0);
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 100; j++)
			G[i * 101 + j].emplace_back(i * MAXC + j + 1, P[i]);

	int q;
	cin >> q;
	vector<int> D(N);
	vector<int> QP(N, -1);
	vector<int> Q;
	Q.reserve(N);

	const auto percolate = [&](int i)
	{
		int j, a = Q[i], b, d = D[a];
		while (i > 0 && (j = (i - 1) / 2, b = Q[j], d < D[b]))
		{
			swap(Q[i], Q[j]);
			swap(QP[a], QP[b]);
			i = j;
		}
		while (j = i * 2 + 2, j < Q.size())
		while (v > 0 && D[v] < D[(v - 1) / 2])
			swap(D[v], D[(v - 1) / 2]);
		while (v * 2 + 2 < Q.size() && D[v] > min(D[v * 2 + 1], D[v * 2 + 2]))
			swap(D[v], )
	};

	const auto push = [&](int v, int d)
	{

	};

	while (q--)
	{
		int c, s, e;
		cin >> c >> s >> e;
		fill_n(D.begin(), N, BIG);
		D[s] = 0;

	}

	delete[] D;
	delete[] QS;
}