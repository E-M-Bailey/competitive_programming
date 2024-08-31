#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

constexpr int K = 300;
int			  n;

ll mpow(ll a, ll b, int M)
{
	ll ans = 1;
	for (; b; a = a * a % M, b /= 2)
		if (b % 2)
			ans = ans * a % M;
	return ans;
}

array<int, 101> mpows(ll a, int M)
{
	array<int, 101> ans{1};
	for (int i = 0; i < 100; i++)
		ans[i + 1] = (int(ans[i] * a % M));
	return ans;
}

constexpr int	A = 29, B = 31;
constexpr int	M = 1000000007, N = 1000000009;
array<int, 101> P = mpows(A, M), Q = mpows(B, N), I = mpows(mpow(A, M - 2, M), M), J = mpows(mpow(B, M - 2, M), M);

vector<pair<int, int>> G[100000];
int					   D[100000], S[100000], I[100000], H[100000], P[100000], H1[100000][101];
int					   ctr;

void dfs1(int v)
{
	S[v] = 1;
	for (auto [w, c] : G[v])
	{
		P[w] = v;
		G[w].erase(find(begin(G[w]), end(G[w]), pair{v, c}));
		D[w] = D[v] + 1;
		dfs1(w);
		S[v] += S[w];
	}
}
void dfs2(int v, int u)
{
	I[v] = ctr++;
	H[v] = u;
	if (S[v] == 1)
		return;
	sort(begin(G[v]),
		 end(G[v]),
		 [](pair<int, int> a, pair<int, int> b)
		 {
			 return S[a.first] > S[b.first];
		 });
	dfs2(G[v][0].first, u);
	for (int i = 1; i < (int)size(G[v]); i++)
	{
		auto [w, c] = G[v][i];
		dfs2(w, w);
	}
}

int main()
{
	cin >> n;
	for (int i = 0; i < n - 1; i++)
	{
		int	 u, v;
		char c;
		cin >> u >> v >> c;
		G[u - 1].emplace_back(v - 1, c - 'a');
		G[v - 1].emplace_back(u - 1, c - 'a');
	}
}
