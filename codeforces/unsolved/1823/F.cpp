#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

constexpr ll mod = 998244353, phi = mod - 1;

int n, s, t;

vector<int> G[200000];
int			P[200000], D[200000], ST[200000], C[200000];

ll mpow(ll a, ll b)
{
	if ((a %= mod) < 0)
		a += mod;
	if ((b %= phi) < 0)
		b += phi;
	ll ans = 1;
	for (; b; a = a * a % mod, b /= 2)
		if (b % 2)
			ans = ans * a % mod;
	return ans;
}

void dfs1(int v)
{
	for (int w : G[v])
		if (w != P[v])
		{
			P[w] = v;
			D[w] = D[v] + 1;
			dfs1(w);
		}
}

void dfs2(int v, ll e)
{
	int up = 0;
	for (int w : G[v])
		up += w == P[v] || ST[D[w]] == w;
	ll uinv = mpow(up, -1);
	ll f	= e * uinv % mod;
	C[v]	= int(f * (int)size(G[v]) % mod);
	for (int w : G[v])
		if (w != P[v] && ST[D[w]] != w)
			dfs2(w, f);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> s >> t;
	s--;
	t--;
	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	P[s] = -1;
	dfs1(s);
	fill_n(ST, n, -1);
	for (int j = t; j >= 0; j = P[j])
		ST[D[j]] = j;
	
	dfs2(s, D[t]);
	for (int i = 1; i < D[t]; i++)
		dfs2(ST[i], 2 * (D[t] - i));
	C[t] = 1;

	for (int i = 0; i < n; i++)
		cout << C[i] << ' ';
}
