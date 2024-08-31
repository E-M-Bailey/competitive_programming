#include <bits/stdc++.h>

using namespace std;

int							   l, b;
vector<int>					   N, A, C;
vector<bool>				   V;
vector<vector<pair<int, int>>> G;

bool dfs(int v, int a)
{
	if (A[v] >= 0 && A[v] != a)
		return false;
	if (V[v])
		return true;
	A[v] = a;
	V[v] = true;
	C.push_back(v);
	for (auto [w, n] : G[v])
		if (!dfs(w, (n - a + 3) % 3))
			return false;
	return true;
}

int main()
{
	cin >> l >> b;
	N.resize(l);
	A.resize(b, -1);
	V.resize(b);
	G.resize(b);
	for (auto &n : N)
	{
		char c;
		cin >> c;
		n = c == 'R' ? 0 : c == 'B' ? 1 : 2;
	}

	vector<vector<int>> L(l);
	for (int v = 0; v < b; v++)
	{
		int k;
		cin >> k;
		for (int i = 0; i < k; i++)
		{
			int a;
			cin >> a;
			a--;
			L[a].push_back(v);
		}
	}

	for (int a = 0; a < l; a++)
	{
		if (L[a].empty())
		{
			if (N[a])
			{
				cout << "impossible";
				return 0;
			}
		}
		else if (size(L[a]) == 1)
		{
			int v = L[a][0];
			if (A[v] >= 0 && A[v] != N[a])
			{
				cout << "impossible";
				return 0;
			}
			A[v] = N[a];
		}
		else
		{
			int u = L[a][0], v = L[a][1];
			G[u].emplace_back(v, N[a]);
			G[v].emplace_back(u, N[a]);
		}
	}

	for (int v = 0; v < b; v++)
		if (!V[v] && A[v] >= 0 && !dfs(v, A[v]))
		{
			cout << "impossible";
			return 0;
		}

	for (int v = 0; v < b; v++)
		if (!V[v])
		{
			int best = -1, bests = INT_MAX;
			for (int a = 0; a < 3; a++)
			{
				C.clear();
				if (dfs(v, a))
				{
					int cur = 0;
					for (int w : C)
						cur += A[w];
					if (cur < bests)
					{
						best  = a;
						bests = cur;
					}
				}
				for (int w : C)
				{
					A[w] = -1;
					V[w] = false;
				}
			}
			if (best < 0)
			{
				cout << "impossible";
				return 0;
			}
			dfs(v, best);
		}
	
	cout << accumulate(begin(A), end(A), 0);
}
