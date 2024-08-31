#include <bits/stdc++.h>

using namespace std;

int					  n, m, k;
vector<multiset<int>> G, T;
vector<int>			  C;

vector<int>			PR;
vector<vector<int>> paths;
vector<bool>		CODD;

void rem(int u, int v)
{
	auto it = G[u].find(v);
	if (it != end(G[u]))
		G[u].erase(it);
	auto jt = G[v].find(u);
	if (jt != end(G[v]))
		G[v].erase(jt);
}

bool dfs(int v, int cc)
{
	CODD[cc] = CODD[cc] || (int)size(G[v]) % 2;
	C[v]	 = cc;
	for (int w : G[v])
	{
		if (C[w] >= 0)
			continue;
		auto up = dfs(w, cc);
		if (!up)
			continue;

		if (PR[v] < 0)
			PR[v] = w;
		else
		{
			paths.emplace_back();
			for (int x = v; x >= 0; x = PR[x])
				paths.back().emplace_back(x);
			reverse(begin(paths.back()), end(paths.back()));
			for (int x = w; x >= 0; x = PR[x])
				paths.back().emplace_back(x);
			PR[v] = -1;
		}
	}

	if (PR[v] < 0)
		return (int)size(G[v]) % 2;
	else if ((int)size(G[v]) % 2 == 0)
		return true;
	else
	{
		paths.emplace_back();
		for (int x = v; x >= 0; x = PR[x])
			paths.back().emplace_back(x);
		return false;
	}
}

vector<int> cyc;
void		expand(list<int> &L)
{
	for (auto it = begin(L); it != end(L); it++)
	{
		int v = *it;
		if (size(G[v]))
		{
			int		  x = v, y = v;
			list<int> nxt;
			while (nxt.push_back(x), (y = *begin(G[x])), rem(x, y), y != v)
			{
				x = y;
			}
			expand(nxt);
			L.splice(it, nxt);
		}
	}
}

int main()
{
	cin >> n >> m >> k;
	G.resize(n);
	C.resize(n, -1);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].insert(v);
		G[v].insert(u);
	}
	T = G;

	PR.resize(n, -1);

	int mink = 0;
	for (int i = 0; i < n; i++)
		mink += (int)size(G[i]) % 2;
	mink /= 2;

	int ctr = 0;
	for (int i = 0; i < n; i++)
		if (C[i] < 0 && !G[i].empty())
		{
			CODD.push_back(false);
			dfs(i, ctr++);
			if (!CODD.back())
				mink++;
		}

	if (k < mink || k > m)
	{
		cout << "Impossible";
		return 0;
	}
	cout << "Possible\n";

	for (auto const &path : paths)
	{
		for (int i = 1; i < (int)size(path); i++)
		{
			int u = path[i - 1], v = path[i];
			rem(u, v);
		}
	}

	vector<list<int>> paths2;
	for (auto const &path : paths)
	{
		paths2.emplace_back(begin(path), end(path));
		expand(paths2.back());
	}

	for (int i = 0; i < n; i++)
		if (C[i] >= 0 && !CODD[C[i]])
		{
			CODD[C[i]] = true;
			paths2.emplace_back(list<int>{i});
			expand(paths2.back());
		}
	
	vector<list<int>> paths3;
	while ((int)(size(paths2) + size(paths3)) < k)
	{
		auto &L = paths2.back();
		if ((int)size(L) == 2)
		{
			paths3.push_back(move(L));
			paths2.pop_back();
		}
		else
		{
			int u = L.back();
			L.pop_back();
			int v = L.back();
			paths3.push_back({u, v});
		}
	}
	while (!paths2.empty())
	{
		paths3.push_back(move(paths2.back()));
		paths2.pop_back();
	}
	for (auto const &L : paths3)
	{
		for (int v : L)
			cout << v + 1 << ' ';
		cout << '\n';
	}
}
