#include <bits/stdc++.h>

using namespace std;

// Based on KACTL
vector<int>					   num, st;
vector<vector<pair<int, int>>> ed;
int							   tim;
template<class F>
int dfs(int at, int par, F &f)
{
	int me = num[at] = ++tim, e, y, top = me;
	for (auto pa : ed[at])
		if (pa.second != par)
		{
			tie(y, e) = pa;
			if (num[y])
			{
				top = min(top, num[y]);
				if (num[y] < me)
					st.push_back(e);
			}
			else
			{
				int si = (int)size(st);
				int up = dfs(y, e, f);
				top	   = min(top, up);
				if (up == me)
				{
					st.push_back(e);
					f(vector<int>(st.begin() + si, st.end()));
					st.resize(si);
				}
				else if (up < me)
					st.push_back(e);
				else // bridge
					f(vector<int>{e});
			}
		}
	return top;
}
template<class F>
void bicomps(F f)
{
	num.assign((int)size(ed), 0);
	for (int i = 0; i < (int)size(ed); i++)
		if (!num[i])
			dfs(i, -1, f);
}

vector<int>			D;
vector<vector<int>> H, P;

void dfs(int v)
{
	for (int w : H[v])
	{
		H[w].erase(find(begin(H[w]), end(H[w]), v));
		D[w] = D[v] + 1;
		P[w].push_back(v);
		while (P[w].size() <= P[P[w].back()].size())
			P[w].push_back(P[P[w].back()][P[w].size() - 1]);
		dfs(w);
	}
}

int lca(int u, int v)
{
	if (D[u] < D[v])
		swap(u, v);
	while (D[u] > D[v])
		u = P[u][__builtin_ctz(D[u] - D[v])];
	int i = 20;
	while (u != v)
	{
		while (i > 0 && (i >= (int)P[u].size() || P[u][i] == P[v][i]))
			i--;
		u = P[u][i];
		v = P[v][i];
	}
	return u;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m, d;
	cin >> n >> m >> d;

	vector<pair<int, int>> E(m);
	ed.resize(n);
	for (int e = 0; e < m; e++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		E[e] = {u, v};
		ed[u].emplace_back(v, e);
		ed[v].emplace_back(u, e);
	}

	int k = 0;

	vector<vector<int>> bccs(n);

	bicomps(
		[&](vector<int> const &es)
		{
			for (int e : es)
			{
				auto [u, v] = E[e];
				if (bccs[u].empty() || bccs[u].back() != k)
					bccs[u].push_back(k);
				if (bccs[v].empty() || bccs[v].back() != k)
					bccs[v].push_back(k);
			}
			k++;
		});

	int num_bccs = k;

	vector<int> art(n);
	for (int i = 0; i < n; i++)
		if (bccs[i].size() > 1)
			art[i] = k++;

	D.resize(k);
	H.resize(k);
	P.resize(k);
	for (int v = 0; v < n; v++)
		if (art[v])
			for (int b : bccs[v])
			{
				H[art[v]].push_back(b);
				H[b].push_back(art[v]);
			}

	dfs(0);

	while (d--)
	{
		int p, q, r, s;
		cin >> p >> q >> r >> s;
		p = art[--p] ? art[p] : bccs[p][0];
		q = art[--q] ? art[q] : bccs[q][0];
		r = art[--r] ? art[r] : bccs[r][0];
		s = art[--s] ? art[s] : bccs[s][0];

		int	 pq = lca(p, q), rs = lca(r, s);
		bool bad = pq == rs;
		if (D[pq] > D[rs])
		{
			int pqr = lca(pq, r), pqs = lca(pq, s), t = P[pq][0];
			bad = pqr == pq || pqs == pq || ((t == pqr || t == pqs) && pq < num_bccs);
		}
		else if (D[pq] < D[rs])
		{
			int prs = lca(p, rs), qrs = lca(q, rs), t = P[rs][0];
			bad = prs == rs || qrs == rs || ((t == prs || t == qrs) && rs >= num_bccs);
		}

		cout << (bad ? "NO\n" : "YES\n");
	}
}
