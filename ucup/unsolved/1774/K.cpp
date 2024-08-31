#include <bits/stdc++.h>

using namespace std;
int n, m;
vector<vector<int>> G;
vector<long long> a, d;
vector<int> h;

void dfs1(int v)
{
	for (int w : G[v])
	{
		G[w].erase(find(begin(G[w]), end(G[w]), v));
		dfs1(w);
	}
	
	switch (size(G[v]))
	{
	case 0:
		a[v] = 1;
		d[v] = 1;
		h[v] = 0;
		break;
	case 1:
		a[v] = 1 + a[G[v][0]] + d[G[v][0]];
		d[v] = 1 + 2 * d[G[v][0]];
		h[v] = 1 + h[G[v][0]];
		break;
	case 2:
		a[v] = 1 + a[G[v][0]] + a[G[v][1]] + d[G[v][0]] + d[G[v][1]] + min(d[G[v][0]], d[G[v][1]]);
		d[v] = 1 + 2 * d[G[v][0]] + 2 * d[G[v][1]];
		h[v] = 1 + max(h[G[v][0]], h[G[v][1]]);
		break;
	}
}

long long ans = LLONG_MAX;

void dfs2(int v, long long A, long long D, int H)
{
	switch(size(G[v]))
	{
	case 0:
		if (1 + H <= 32)
			ans = min(ans, A);
		break;
	case 1:
		if (1 + max(H, h[G[v][0]]) < 32)
			ans = min(ans, a[v] + A + D + min(D, d[G[v][0]]));
		dfs2(G[v][0], 1 + A + D, 1 + 2 * D, 1 + H);
		break;
	case 2:
		dfs2(G[v][0], 1 + a[G[v][1]] + A + d[G[v][1]] + D + min(d[G[v][1]], D), 1 + 2 * d[G[v][1]] + 2 * D, 1 + max(H, h[G[v][1]]));
		dfs2(G[v][1], 1 + a[G[v][0]] + A + d[G[v][0]] + D + min(d[G[v][0]], D), 1 + 2 * d[G[v][0]] + 2 * D, 1 + max(H, h[G[v][0]]));
		break;
	}
}
void dfs2(int v)
{
	switch(size(G[v]))
	{
	case 0:
		ans = 0;
		break;
	case 1:
		if (1 + h[G[v][0]] <= 32)
			ans = min(ans, a[G[v][0]]);
		dfs2(G[v][0], 1, 1, 0);
		break;
	case 2:
		if (1 + max(h[G[v][0]], h[G[v][1]]) < 32)
			ans = min(ans, a[v]);
		dfs2(G[v][0], 1 + a[G[v][1]] + d[G[v][1]], 1 + 2 * d[G[v][1]], 1 + h[G[v][1]]);
		dfs2(G[v][1], 1 + a[G[v][0]] + d[G[v][0]], 1 + 2 * d[G[v][0]], 1 + h[G[v][0]]);
		break;
	}
}

int main()
{
	cin >> n >> m;
	G.resize(n);
	bool bad = m != n - 1;
	for (int i = 0; i < m; i++)
	{
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		G[x].push_back(y);
		G[y].push_back(x);
		bad |= size(G[x]) > 3 || size(G[y]) > 3;
	}
	if (bad)
	{
		cout << "NIE";
		return 0;
	}


	a.resize(n);
	d.resize(n);
	h.resize(n);

	int s = 0;
	while (size(G[s]) == 3)
		s++;
	dfs1(s);
	dfs2(s);

	if (ans == LLONG_MAX)
		cout << "NIE";
	else
		cout << ans;
}

