#include <bits/stdc++.h>
using namespace std;

int					n, s, t, N;
vector<vector<int>> A;

deque<int>			 B;
vector<int>			 L, I;
vector<vector<int>>	 G;
vector<vector<bool>> C;

void add(int u, int v)
{
	G[u].push_back(v);
	G[v].push_back(u);
	C[u][v] = true;
}

bool dfs(int u)
{
	if (u == t)
		return true;
	for (int &i = I[u]; i < size(G[u]); i++)
	{
		int v = G[u][i];
		if (L[v] == L[u] + 1 && C[u][v] && dfs(v))
		{
			C[u][v] = false;
			C[v][u] = true;
			return true;
		}
	}
	return false;
}

void reset(int th)
{
	for (vector<bool> &CC : C)
		fill(begin(CC), end(CC), false);
	for (int i = 0; i < n; i++)
	{
		add(s, i + 1);
		add(i + n + 1, t);
		for (int j = 0; j < n; j++)
			if (A[i][j] >= th)
				add(i + 1, j + n + 1);
	}
}

int flow(int th)
{
	reset(th);
	int f = 0;
	do
	{
		L.assign(N, 0);
		I.assign(N, 0);
		B.clear();
		B.push_back(s);
		L[s] = 1;
		while (!B.empty() && L[t] == 0)
		{
			int u = B.front();
			B.pop_front();
			for (int v : G[u])
			{
				if (L[v] == 0 && C[u][v])
				{
					L[v] = L[u] + 1;
					B.push_back(v);
				}
			}
		}

		B.clear();
		while (dfs(s))
			f++;
	}
	while (L[t] != 0);
	return f;
}

int main()
{
	cin >> n;
	s = 0;
	t = 2 * n + 1;
	N = 2 * n + 2;
	G.resize(N);
	A.assign(n, vector<int>(n));
	C.assign(N, vector<bool>(N));
	for (auto &AA : A)
		for (int &a : AA)
			cin >> a;

	int lo = 1, hi = 1e6;
	while (lo < hi)
	{
		int	 th	   = (lo + hi + 1) / 2;
		int	 f	   = flow(th);
		bool works = f == n;
		if (works)
			lo = th;
		else
			hi = th - 1;
	}
	cout << lo;
}
