#include <bits/stdc++.h>

using namespace std;

int main()
{
	int s, p, t;
	cin >> s >> p >> t;
	s += 2;

	const int trash = s - 2, terminal = s - 1;
	vector<array<int, 53>> G(s);
	const auto tr = [&G](int v, char c) -> int&
	{
		if ('a' <= c && c <= 'z')
			return G[v][c - 'a'];
		else if ('A' <= c && c <= 'Z')
			return G[v][c - 'A' + 26];
		else
			return G[v][52];
	};
	for (int i = 0; i < s; i++)
	{
		for (int c = 'a'; c <= 'z'; c++)
			tr(i, c) = trash;
		for (int c = 'A'; c <= 'Z'; c++)
			tr(i, c) = trash;
		tr(i, '$') = trash;
	}
	while (p--)
	{
		int u;
		cin >> u;
		u--;
		tr(u, '$') = terminal;
	}
	while (t--)
	{
		int u, v;
		char c;
		cin >> u >> c >> v;
		u--;
		v--;
		tr(u, c) = v;
	}

	int N = s * s;
	vector<vector<int>> G2(N * 4, vector<int>(N * 4, INT_MAX));
	const auto add = [&G2](int u, int v, int wt)
	{
		G2[u][v] = min(G2[u][v], wt);
	};
	const auto adds = [s, N, add, &G2](int ui, int uj, int vi, int vj, const array<int, 4>& A, int wt)
	{
		int u = ui * s + uj, v = vi * s + vj;
		for (int i = 0; i < 4; i++)
			if (A[i] >= 0)
				add(u + i * N, v + A[i] * N, wt);
	};

	const array<int, 4> aa{ 0, -1, -1, 3 }, ab{ 3, -1, -1, 3 }, a_{ 1, 1, -1, 1 }, _a{ 2, -1, 2, 2 }, AA{ 0, 3, 3, 3 };

	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++)
		{
			for (char a = 'a'; a <= 'z'; a++)
			{
				adds(i, j, tr(i, a), tr(j, a), aa, 2);
				for (char b = 'a'; b <= 'z'; b++)
					if (a != b)
						adds(i, j, tr(i, a), tr(j, b), ab, 2);
				adds(i, j, tr(i, a), j, a_, 1);
				adds(i, j, i, tr(j, a), _a, 1);
			}
			for (char A = 'A'; A <= 'Z'; A++)
				adds(i, j, tr(i, A), tr(j, A), AA, 2);
			adds(i, j, tr(i, '$'), tr(j, '$'), AA, 2);
		}

	vector<int> D(N * 4, INT_MAX);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
	Q.emplace(0, 0);
	while (!Q.empty())
	{
		auto [d, u] = Q.top();
		Q.pop();
		if (D[u] < INT_MAX)
			continue;
		D[u] = d;
		for (int v = 0; v < 4 * N; v++)
		{
			int wt = G2[u][v];
			if (wt < INT_MAX && D[v] == INT_MAX)
				Q.emplace(d + wt, v);
		}
	}

	int d = D[(s - 1) * s + (s - 1) + 3 * N];
	cout << (d == INT_MAX ? -1 : d - 2);
}
