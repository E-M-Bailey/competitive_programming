#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<unordered_set<int>> G(n);
	while (m--)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		G[a].insert(b);
		G[b].insert(a);
	}

	unordered_set<int> O;
	for (int i = 0; i < n; i++)
		if (G[i].size() % 2)
			O.insert(i);

	int ans = (int)O.size();
	vector<pair<int, int>> ed;

	vector<int> path;
	unordered_map<int, int> pathidx;

	while (!O.empty())
	{
		int s = *begin(O);
		path.assign(1, s);
		pathidx.clear();
		pathidx[s] = 0;

		do
		{
			int u = path.back();
			int v = *G[u].begin();
			if (path.size() >= 2 && v == path[path.size() - 2])
				v = *next(G[u].begin());
			auto [it, ins] = pathidx.emplace(v, path.size());
			path.push_back(v);
			if (!ins)
			{
				int st = it->second;
				for (int i = st; i < (int)path.size() - 1; i++)
				{
					ed.emplace_back(path[i], path[i + 1]);
					G[path[i]].erase(path[i + 1]);
					G[path[i + 1]].erase(path[i]);
					pathidx.erase(path[i + 1]);
				}
				path.resize(st + 1);
				pathidx.emplace(v, st);
			}
			if (G[v].size() % 2 == 1)
			{
				for (int i = 0; i < (int)path.size() - 1; i++)
				{
					ed.emplace_back(path[i], path[i + 1]);
					G[path[i]].erase(path[i + 1]);
					G[path[i + 1]].erase(path[i]);
					pathidx.erase(path[i + 1]);
				}
				pathidx.erase(path.back());
				pathidx.clear();
				path.clear();
				if (v != s)
				{
					O.erase(s);
					O.erase(v);
				}
				break;
			}
		} while (path.size() > 1);
	}

	for (int s = 0; s < n; s++)
	{
		while (!G[s].empty())
		{
			path.assign(1, s);
			pathidx.clear();
			pathidx[s] = 0;

			do
			{
				int u = path.back();
				int v = *G[u].begin();
				//cerr << s << ' ' << u << ' ' << v << endl;
				if (path.size() >= 2 && v == path[path.size() - 2])
					v = *next(G[u].begin());
				auto [it, ins] = pathidx.emplace(v, path.size());
				path.push_back(v);
				if (!ins)
				{
					int st = it->second;
					//for (int p : path)
					//	cerr << ' ' << p;
					//cerr << endl;
					for (int i = st; i < (int)path.size() - 1; i++)
					{
						ed.emplace_back(path[i], path[i + 1]);
						G[path[i]].erase(path[i + 1]);
						G[path[i + 1]].erase(path[i]);
						pathidx.erase(path[i + 1]);
					}
					path.resize(st + 1);
					pathidx.emplace(v, st);
				}
			} while (path.size() > 1);
		}
	}

	cout << ans << '\n';
	for (auto [a, b] : ed)
		cout << a + 1 << ' ' << b + 1 << '\n';
}