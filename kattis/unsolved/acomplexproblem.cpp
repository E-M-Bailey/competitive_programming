#include <bits/stdc++.h>

using namespace std;

// Source: KACTL
vector<int> val, comp, z, cont;
int tim, ncomps;
template <class G, class F>
int dfs(int j, G &g, F &f)
{
	int low = val[j] = ++tim, x;
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
		} while (x != j);
		f(cont);
		cont.clear();
		ncomps++;
	}
	return val[j] = low;
}
template <class G, class F>
void scc(G &g, F f)
{
	int n = sz(g);
	val.assign(n, 0);
	comp.assign(n, -1);
	tim = ncomps = 0;
	for (int i = 0; i < n; i++)
		if (comp[i] < 0)
			dfs(i, g, f);
}

int n;
vector<pair<int, int>> EW, ES;
vector<vector<int>> GW, GS;

vector<string> names;
unordered_map<string, int> ids;
int id()
{
	static string str;
	cin >> str;
	auto [it, ins] = ids.emplace(str, (int)ids.size());
	n += ins;
	if (ins)
		names.push_back(move(str));
	return it->second;
}

struct dso
{
	vector<int> P, R;
	
}

int main()
{
	int nw, ns;
	cin >> nw >> ns;
	EW.resize(nw);
	ES.resize(ns);
	for (auto &[u, v] : EW)
		u = id(), v = id();
	for (auto &[u, v] : ES)
		u = id(), v = id();

	GW.resize(n);
	GS.resize(n);
	for (auto [u, v] : EW)
		GW[u].push_back(v), GW[v].push_back(u);
	for (auto [u, v] : ES)
		GS[u].push_back(v), GS[v].push_back(u);
	
	
}