#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for(int i = a; i<(b); ++i)
#define ALL(x) begin(x), end(x)
#define sz(x) int(size(x))
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int T;
	cin >> T;
	while (T--)
	{
		int n, m;
		cin >> n >> m;
		int k = 0;
		const auto idx = [&](int i, int j)
		{
			return 2 * m * i + j;
		};

		vector<int> G(4 * n * m, -1);
		rep(i, 0, n) rep(j, 0, m)
		{
			char x, y;
			cin >> x >> y;
			int a = idx(2 * i, 2 * j), b = idx(2 * i, 2 * j + 1), c = idx(2 * i + 1, 2 * j), d = idx(2 * i + 1, 2 * j + 1);
			if ((i + j) % 2 == 0)
				swap(b, c);
			if (x == '0') G[a] = G[b] = k++;
			if (y == '0') G[c] = G[d] = k++;
		}

		vector<bitset<4>> X(k);
		rep(i, 0, 2 * n) if (int j = G[idx(i, 0)]; j >= 0) X[j][0] = true;
		rep(i, 0, 2 * n) if (int j = G[idx(i, 2 * m - 1)]; j >= 0) X[j][1] = true;
		rep(i, 0, 2 * m) if (int j = G[idx(0, i)]; j >= 0) X[j][2] = true;
		rep(i, 0, 2 * m) if (int j = G[idx(2 * n - 1, i)]; j >= 0) X[j][3] = true;

		vector<unordered_set<int>> E(k);
		const auto edge = [&](int u, int v)
		{
			if (u >= 0 && v >= 0 && u != v)
			{
				E[u].insert(v);
				E[v].insert(u);
			}
		};

		rep(i, 0, 2 * n) rep(j, 0, 2 * m)
		{
			if (i) edge(G[idx(i, j)], G[idx(i - 1, j)]);
			if (j) edge(G[idx(i, j)], G[idx(i, j - 1)]);
		}

		vector<bool> vis(k);
		unordered_set<int> CC;
		unordered_set<int> SD[4]{};
		bool done = false;
		rep(i, 0, 2 * n)
		{
			if (done) break;
			rep(j, 0, 2 * m)
			{
				if (done) break;
				int a = G[idx(i, j)];
				if (a <= 0 || vis[a])
					continue;
				bitset<4> x;
				queue<int> Q;
				Q.push(a);
				while (!Q.empty())
				{
					int v = Q.front();
					Q.pop();
					if (vis[v])
						continue;
					vis[v] = true;
					CC.insert(v);
					rep(r, 0, 4)
						if (X[v][r])
							SD[r].insert(v);
					x |= X[v];
					for (int w : E[v])
						if (!vis[w])
							Q.push(w);
				}
				if (x.all())
				{
					done = true;
					break;
				}
				CC.clear();
				rep(r, 0, 4)
					SD[r].clear();
			}
		}

		if (CC.empty())
		{
			cout << "NO MINIMAL CORRIDOR\n";
			continue;
		}

		vector<bool> mark(k, false);
		rep(r, 0, 4)
			if (sz(SD[r]) == 1)
				mark[*SD[r].begin()] = true;

		struct bicomps
		{
			vi num, st;
			vector<vector<pii>> ed;
			int Time = 0;
			vector<bool> AP;
			int dfs(int at, int par)
			{
				int deg = 0;
				int me = num[at] = ++Time, e, y, top = me;
				for (auto pa : ed[at]) if (pa.second != par)
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
						deg++;
						int si = sz(st);
						int up = dfs(y, e);
						top = min(top, up);
						if (up == me)
						{
							AP[at] = true;
							st.push_back(e);
							st.resize(si);
						}
						else if (up < me) st.push_back(e);
						else { AP[at] = true; }

					}
				}
				if (par < 0)
					AP[at] = deg > 1;
				return top;
			}

			bicomps(unordered_set<int> &CC, vector<unordered_set<int>> &E) :
				num(sz(E)),
				ed(sz(E)),
				AP(sz(E))
			{
				int eid = 0;
				for (int u : CC)
					for (auto v : E[u])
						if (u < v)
						{
							ed[u].emplace_back(v, eid);
							ed[v].emplace_back(u, eid++);
						}
				rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1);
				for (int i : CC)
					if (sz(E[i]) == 1)
						AP[i] = false;
			}
		} bc(CC, E);

		bool good = true;

		for (int i : CC)
			good &= mark[i] || bc.AP[i];

		if (good)
			cout << sz(CC) << '\n';
		else
			cout << "NO MINIMAL CORRIDOR\n";
	}
}
