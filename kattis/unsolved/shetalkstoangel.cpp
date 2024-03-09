#include <bits/stdc++.h>

using namespace std;

typedef double F;

int n;
F ca, cb;
vector<vector<int>> G;
vector<vector<int>> chores;
vector<bool> has;
vector<vector<pair<F, F>>> DP;

void dfs1(int u, int v)
{
	for (int w : G[v])
		if (w != u)
		{
			dfs1(v, w);
			if (has[w])
				has[v] = true;
		}
	
}

void dfs2(int u, int v)
{
	for (int w : G[v])
		if (w != u && has[w])
			dfs2(v, w);
	
	
}

int main()
{
	int c;
	cin >> n >> c;
	{
		int k, l;
		cin >> k >> l;
		ca = (F)1 / k;
		cb = (F)1 / l;
	}
	for (int i = 0; i < c; i++)
	{
		int p;
		cin >> p;
		chores[p - 1].push_back(i);
		has[p - 1] = true;
	}
	G.resize(n);
	DP.resize(n);
	for (int i = 1; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		G[a].push_back(b);
		G[b].push_back(a);
	}


}