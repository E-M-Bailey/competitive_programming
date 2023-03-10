#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> G;
vector<int> C;
vector<int> A;
vector<vector<int>> IC;
int lo = numeric_limits<int>::max();
int hi = numeric_limits<int>::min();

vector<bool> S, V;
vector<vector<int>> IG;
vector<bool> SM;

int dfs1(int v)
{
	if (S[v])
	{
		IC.emplace_back();
		return v;
	}
	if (V[v])
		return -1;
	S[v] = true;
	V[v] = true;
	int c = dfs1(G[v]);
	S[v] = false;
	if (c >= 0)
	{
		C[v] = size(IC) - 1;
		IC.back().push_back(v);
	}
	return c == v ? -1 : c;
}

int dfs2(int v, int64_t& tot)
{
	int w = v < n;

	bool s = v == n ? true : SM[A[v] - lo];
	if (v != n)
		SM[A[v] - lo] = true;
	for (int u : IG[v])
		if (C[u] < 0 || C[u] != C[v])
			w += dfs2(u, tot);
	if (v != n)
		SM[A[v] - lo] = s;
	if (!s)
		tot += w;
	return w;
}

int main()
{
	cin >> n;
	A.resize(n);
	G.resize(n + 1);
	IG.resize(n + 1);
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
		lo = min(lo, A[i]);
		hi = max(hi, A[i]);
		G[i] = i + A[i];
		if (G[i] < 0 || G[i] >= n)
			G[i] = n;
		IG[G[i]].push_back(i);
	}

	G[n] = n;
	IG[n].push_back(n);
	C.resize(n + 1, -1);
	S.resize(n + 1);
	V.resize(n + 1);
	for (int i = 0; i < n; i++)
		dfs1(i);
	SM.resize(hi - lo + 1);
	int64_t tot = 0;
	for (const auto& CC : IC)
	{
		int cnt = 0, num = 0;
		for (int v : CC)
		{
			if (v == n) continue;
			num += !SM[A[v] - lo];
			SM[A[v] - lo] = true;
		}
		for (int v : CC)
			cnt += dfs2(v, tot);
		if (CC[0] != n)
			tot += (int64_t)cnt * num;
		for (int v : CC)
			if (v != n)
				SM[A[v] - lo] = false;
	}
	cout << tot << endl;
}