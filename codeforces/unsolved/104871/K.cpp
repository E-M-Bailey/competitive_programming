#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> G, T;
vector<int>			P;
vector<bool>		vis;

void dfs(int v)
{
	vis[v] = true;
	for (int w : G[v])
		if (!vis[w])
		{
			P[w] = v;
			T[v].push_back(w);
			dfs(w);
		}
}

int main()
{
	int n, m;
	cin >> n >> m;
	G.resize(n);
	T.resize(n);
	P.resize(n);
	vis.resize(n);
	map<pair<int, int>, int> E;
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
		E[{u, v}] = E[{v, u}] = i;
	}
	dfs(1);

	if (size(G[1]) == size(T[1]))
	{
		cout << "No solution";
		return 0;
	}

	int s = 0;
	while (P[G[1][s]] == 1)
		s++;
	s = G[1][s];

	vector<int> zo{0};
	while (zo.back() != 1)
		zo.push_back(P[zo.back()]);

	vector<int> cyc{s};
	while (cyc.back() != 1)
		cyc.push_back(P[cyc.back()]);

	vector<int> comm;
	while (!cyc.empty() && !zo.empty() && cyc.back() == zo.back())
	{
		comm.push_back(cyc.back());
		cyc.pop_back();
		zo.pop_back();
	}
	zo.push_back(comm.back());
	cyc.push_back(comm.back());
	reverse(begin(comm), end(comm));
	cyc.insert(begin(cyc), 1);

	set<int> zos(begin(zo), end(zo));

	set<int>	key1, key2, key12;
	vector<int> p1a, p1b, p2a, p2b;
	for (int i = 1; i < (int)size(zo); i++)
	{
		int k = E[{zo[i - 1], zo[i]}];
		key1.insert(k);
		key12.insert(k);
		p1a.push_back(zo[i]);
	}
	for (int i = 1; i < (int)size(comm); i++)
	{
		key1.insert(E[{comm[i - 1], comm[i]}]);
		p1b.push_back(comm[i]);
	}

	for (int i = 1; i < (int)size(cyc); i++)
	{
		int k = E[{cyc[i - 1], cyc[i]}];
		key2.insert(k);
		p2a.push_back(cyc[i]);
	}
	p2b = {rbegin(zo), rend(zo)};
	p2b.erase(begin(p2b));

	if (p1a.back() == 1)
	{
		int t = cyc[size(cyc) - 2];
		p1a.push_back(t);
		p1b.push_back(1);
		p2a.pop_back();
		vector<int> add{rbegin(p2a) + 1, rend(p2a)};
		add.push_back(1);
		p2b.insert(begin(p2b), begin(add), end(add));
		key1.insert(E[{t, 1}]);
		key2.erase(E[{t, 1}]);
	}

	for (int k : key1)
		cout << k << ' ';
	cout << '\n';
	for (int k : key2)
		cout << k << ' ';
	cout << '\n';

	for (int v : p1a)
		cout << "MOVE " << v << '\n';
	cout << "DROP";
	for (int k : key12)
		cout << ' ' << k;
	cout << '\n';
	for (int v : p1b)
		cout << "MOVE " << v << '\n';
	cout << "DONE\n";
	for (int v : p2a)
		cout << "MOVE " << v << '\n';
	cout << "GRAB\n";
	for (int v : p2b)
		cout << "MOVE " << v << '\n';
	cout << "DONE\n";
}
