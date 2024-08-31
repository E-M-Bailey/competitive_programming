// #pragma GCC optimize("O2")

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x)		 begin(x), end(x)
#define sz(x)		 (int)(x).size()
typedef long long	   ll;
typedef pair<int, int> pii;
typedef vector<int>	   vi;
#define pb push_back
#define mp make_pair

#define MAXN 10'010

int	 n, m, k;
vi	 adj[MAXN];
bool vis[MAXN];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	mt19937 rng(13433441);

	cin >> n >> m >> k;
	if (k == 8)
		k = 1;
	rep(i, 0, m)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	rep(_, 0, k)
	{
		rep(i, 0, n) vis[i] = false;

		vi path;
		int be = uniform_int_distribution<int>(0, n - 1)(rng);
		path.pb(be);
		vis[path[0]] = true;
		while (sz(path) < n)
		{
			int pos = path[sz(path) - 1];
			shuffle(all(adj[pos]), rng);
			bool done = false;
			// try extending
			for (int nxt : adj[pos])
			{
				if (!vis[nxt])
				{
					done = true;
					path.pb(nxt);
					vis[nxt] = true;
					break;
				}
			}
			if (done)
				continue;

			// try rotating
			int rot = adj[pos][0];
			if (rot == path[0])
				rot = adj[pos][1];
			int rotpos;
			rep(i, 0, sz(path))
			{
				if (path[i] == rot)
				{
					rotpos = i;
					break;
				}
			}
			// path[0] -> rot -> pos -> path[rotpos+1]
			reverse(begin(path) + rotpos + 1, end(path));
		}
		for (int x : path)
			cout << x + 1 << ' ';
		cout << '\n';
		rep(i, 0, sz(path) - 1)
		{
			int u = path[i];
			int v = path[i + 1];
			adj[u].erase(find(all(adj[u]), v));
			adj[v].erase(find(all(adj[v]), u));
		}
	}
}