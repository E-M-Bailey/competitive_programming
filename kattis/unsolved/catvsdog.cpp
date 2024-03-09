#include <bits/stdc++.h>

using namespace std;

bool dfs(int a, int L, vector<vector<int>> &G, vector<int> &btoa, vector<int> &A, vector<int> &B)
{
	if (A[a] != L)
		return 0;
	for (int b : G[a])
		if (B[b] == L + 1)
		{
			B[b] = 0;
			if (btoa[b] == -1 || dfs(btoa[b], L + 1, G, btoa, A, B))
				return btoa[b] = a, 1;
		}
	return 0;
}

int hopcroftKarp(vector<vector<int>> &G, vector<int> &btoa)
{
	int res = 0;
	vector<int> A(G.size()), B(btoa.size()), cur, next;
	for (;;)
	{
		fill(begin(A), end(A), 0);
		fill(begin(B), end(B), 0);
		cur.clear();
		for (int a : btoa)
			if (a != -1)
				A[a] = -1;
		for (int a = 0; a < (int)size(G); a++)
			if (A[a] == 0)
				cur.push_back(a);
		for (int lay = 1;; lay++)
		{
			bool islast = 0;
			next.clear();
			for (int a : cur)
				for (int b : G[a])
				{
					if (btoa[b] == -1)
					{
						B[b] = lay;
						islast = 1;
					}
					else if (btoa[b] != a && !B[b])
					{
						B[b] = lay;
						next.push_back(btoa[b]);
					}
				}
			if (islast)
				break;
			if (next.empty())
				return res;
			for (int a : next)
				A[a] = lay;
			cur.swap(next);
		}
		for (int a = 0; a < (int)G.size(); a++)
			res += dfs(a, 0, G, btoa, A, B);
	}
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int c, d, v;
		cin >> c >> d >> v;

		vector<pair<int, int>> A, B;
		for (int i = 0; i < v; i++)
		{
			string a, b;
			cin >> a >> b;
			bool cat = a.front() == 'C';
			int x = atoi(a.c_str() + 1) - 1, y = atoi(b.c_str() + 1) - 1;
			if (cat)
				A.emplace_back(x, y);
			else
				B.emplace_back(y, x);
		}

		int m = A.size(), n = B.size();
		vector<vector<int>> G(m);

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (A[i].first == B[j].first || A[i].second == B[j].second)
				{
					G[i].push_back(j);
				}
			}
		}

		vector<int> btoa(m, -1);
		cout << v - hopcroftKarp(G, btoa) << '\n';
	}
}