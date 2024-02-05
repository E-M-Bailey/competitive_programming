#include <bits/stdc++.h>

using namespace std;

vector<array<int, 3>> cmpMoves()
{
	const array<int, 5>	  O{0, 1, 3, 6, 10};
	vector<array<int, 3>> ans;
	const auto			  add = [&](int ai, int aj, int bi, int bj, int ci, int cj)
	{
		ans.push_back(array<int, 3>{O[ai] + aj, O[bi] + bj, O[ci] + cj});
		ans.push_back(array<int, 3>{O[ci] + cj, O[bi] + bj, O[ai] + aj});
	};
	for (int i = 2; i < 5; i++)
		for (int j = 0; j <= i - 2; j++)
			add(i, j, i, j + 1, i, j + 2);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j <= i; j++)
		{
			add(i, j, i + 1, j, i + 2, j);
			add(i, j, i + 1, j + 1, i + 2, j + 2);
		}
	return ans;
}

const vector<array<int, 3>> MV = cmpMoves();

vector<int> G;

int f(vector<int> &G)
{
	bool found = false;
	int	 ans   = INT_MIN;
	for (array<int, 3> mv : MV)
	{
		int a = mv[0], b = mv[1], c = mv[2];
		if (G[a] == 0 || G[b] == 0 || G[c] != 0)
			continue;
		found  = true;
		int ga = G[a], gb = G[b];
		G[a] = 0;
		G[b] = 0;
		G[c] = ga;
		ans	 = max(ans, ga * gb - f(G));
		G[a] = ga;
		G[b] = gb;
		G[c] = 0;
	}
	return found ? ans : 0;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	vector<int> G(15);
	for (int &g : G)
		cin >> g;
	cout << f(G);
}
