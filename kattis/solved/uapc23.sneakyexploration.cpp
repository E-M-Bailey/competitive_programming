#include <bits/stdc++.h>

using namespace std;

vector<int> S;
vector<vector<int>> G;

int n;
int r = -1;

void dfs1(int u, int v)
{
	S[v] = 1;
	for (int w : G[v])
	{
		if (w == u) continue;
		dfs1(v, w);
		S[v] += S[w];
	}
}

void dfs2(int u, int v, int up)
{
	int cs = up;
	for (int w : G[v])
	{
		if (w == u) continue;
		dfs2(v, w, up + S[v] - S[w]);
		if (r >= 0)
			return;
		cs = max(cs, S[w]);
	}
	//cerr << v << ' ' << cs << endl;
	if (cs * 2 <= n)
		r = v;
}

void dfs3(int u, int v, vector<int>& V)
{
	V.push_back(v);
	for (int w : G[v])
	{
		if (w == u) continue;
		dfs3(v, w, V);
	}
}

int main()
{
	cin >> n;
	S.resize(n);
	G.resize(n);
	int md = 0;
	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
		G[v].push_back(u);
		md = max({ md, (int)size(G[u]), (int)size(G[v]) });
	}

	if (n == 1)
	{
		cout << 1;
		return 0;
	}
	if (md == n - 1)
	{
		cout << -1;
		return 0;
	}

	dfs1(-1, 0);
	dfs2(-1, 0, 0);

	cerr << r << endl;

	vector<vector<int>> V;

	for (int w : G[r])
	{
		V.emplace_back();
		dfs3(r, w, V.back());
	}

	const auto cmp = [&](int i, int j)
	{
		return size(V[i]) < size(V[j]);
	};

	priority_queue<int, vector<int>, decltype(cmp)> PQ(cmp);

	for (int i = 0; i < size(G[r]); i++)
		PQ.push(i);

	int add = -1;
	vector<int> ans{r};
	while (size(ans) < n)
	{
		int i = PQ.top();
		PQ.pop();
		if (add >= 0)
			PQ.push(add);
		ans.push_back(V[i].back());
		V[i].pop_back();
		add = i;
	}

	for (int a : ans)
		cout << a + 1 << ' ';
}