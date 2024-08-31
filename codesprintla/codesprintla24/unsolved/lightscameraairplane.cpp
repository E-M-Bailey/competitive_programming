#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Source: KACTL
ll euclid(ll a, ll b, ll &x, ll &y)
{
	if (!b)
		return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a / b * x, d;
}
ll crt(ll a, ll m, ll b, ll n)
{
	if (n > m)
		swap(a, b), swap(m, n);
	ll x, y, g = euclid(m, n, x, y);
	assert((a - b) % g == 0); // else no solution
	x = (b - a) % n * x % n / g * m + a;
	return x < 0 ? x + m * n / g : x;
}

int						 n, t;
vector<vector<int>>		 G;
vector<int>				 F;
map<pair<int, int>, int> E;

ll cnt(ll x, ll m, ll e)
{
	if (x >= e)
		return 0;
	return (e - x + (m - 1)) / m;
}

void dfs1(int v, int e, ll x, ll m)
{
	if (G[v].empty())
		F[v] += int(cnt(x, m, e));
	for (int i = 0; i < (int)size(G[v]); i++)
	{
		int w = G[v][i];
		ll	X, M;
		if ((x - i) % gcd(m, (ll)size(G[v])))
		{
			X = INT_MAX;
			M = INT_MAX;
		}
		else
		{
			X = crt(x, m, i, (ll)size(G[v]));
			M = lcm(m, (ll)size(G[v]));
		}
		M		= min(M, 1000000009ll);
		X		= min(X, 1000000008ll);
		int e2	= min(e, E[{v, w}]);
		int cur = int(cnt(X, M, e) - cnt(X, M, e2));
		F[v] += cur;
		dfs1(w, e2, X, M);
	}
}

int main()
{
	cin >> n >> t;
	G.resize(n);
	F.resize(n);
	for (int v = 0; v < n; v++)
	{
		int k;
		cin >> k;
		G[v].resize(k);
		for (int &u : G[v])
		{
			cin >> u;
			u--;
		}
	}
	for (int i = 0; i < n - 1; i++)
	{
		int u, v, e;
		cin >> u >> v >> e;
		u--;
		v--;
		e--;
		E[{u, v}] = E[{v, u}] = e;
	}
	dfs1(0, t, 0, 1);

	for (int f : F)
		cout << f << ' ';
}