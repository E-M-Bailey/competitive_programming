#include <bits/stdc++.h>

using namespace std;

#define sz(C)		 (int(size(C)))
#define rep(i, a, b) for (int i = (a); i < (b); i++)

// Source: KACTL
vector<int> val, comp, z, cont;
int			Time, ncomps;
template<class G, class F>
int dfs(int j, G &g, F &f)
{
	int low = val[j] = ++Time, x;
	z.push_back(j);
	for (auto e : g[j])
		if (comp[e] < 0)
			low = min(low, val[e] ?: dfs(e, g, f));

	if (low == val[j])
	{
		do
		{
			x = z.back();
			z.pop_back();
			comp[x] = ncomps;
			cont.push_back(x);
		}
		while (x != j);
		f(cont);
		cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template<class G, class F>
void scc(G &g, F f)
{
	int n = sz(g);
	val.assign(n, 0);
	comp.assign(n, -1);
	Time = ncomps = 0;
	rep(i, 0, n) if (comp[i] < 0) dfs(i, g, f);
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
	}
	vector<vector<int>> C;
	scc(G,
		[&](vector<int> &CC)
		{
			C.push_back(CC);
		});

	vector<vector<pair<int, int>>> G2(2 * n);
	vector<int>					   P, GC;
	vector<vector<int>>			   D;
	for (int ci = 0; ci < ncomps; ci++)
	{
		auto &CC = C[ci];
		int	  ck = sz(CC);

		GC.assign(ck, 0);
		for (int i = 0; i < ck; i++)
			for (int ccj : G[CC[i]])
				if (comp[ccj] == ci)
					GC[i] |= 1 << int(find(begin(CC), end(CC), ccj) - begin(CC));
		D.assign(ck, vector<int>(ck, -1));

		for (int mask = 1; mask < (1 << ck); mask++)
		{
			P.clear();
			for (int i = 0; i < ck; i++)
				if (mask & (1 << i))
					P.push_back(i);
			do
			{
				bool good = true;
				for (int i = 1; i < sz(P); i++)
					if (!(GC[P[i - 1]] & (1 << P[i])))
					{
						good = false;
						break;
					}
				if (!good)
					continue;
				D[P.front()][P.back()] = max(D[P.front()][P.back()], sz(P) - 1);
			}
			while (next_permutation(begin(P), end(P)));
		}

		for (int i = 0; i < ck; i++)
			for (int j = 0; j < ck; j++)
				G2[CC[i]].emplace_back(CC[j] + n, D[i][j]);
	}
	for (int i = 0; i < n; i++)
		for (int j : G[i])
			if (comp[i] != comp[j])
				G2[i + n].emplace_back(j, 1);

	vector<int> D2(2 * n, 1);
	vector<int> I(2 * n);
	for (int i = 0; i < 2 * n; i++)
		for (auto [j, wt] : G2[i])
			I[j]++;
	vector<int> I0;
	for (int i = 0; i < 2 * n; i++)
		if (I[i] == 0)
			I0.push_back(i);
	while (!I0.empty())
	{
		int i = I0.back();
		I0.pop_back();
		for (auto [j, wt] : G2[i])
		{
			D2[j] = max(D2[j], D2[i] + wt);
			if (--I[j] == 0)
				I0.push_back(j);
		}
	}
	cout << *max_element(begin(D2), end(D2));
}
