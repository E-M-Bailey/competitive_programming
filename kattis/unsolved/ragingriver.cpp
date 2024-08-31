#include <bits/extc++.h>

using namespace std;

#define all(C)		 begin(C), end(C)
#define rep(i, a, b) for (int i = (a); i < (b); i++)

typedef long long	   ll;
typedef vector<int>	   vi;
typedef pair<int, int> pii;

// Source: KACTL
const ll		   INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;
struct MCMF
{
	int			N;
	vector<vi>	ed, red;
	vector<VL>	cap, flow, cost;
	vi			seen;
	VL			dist, pi;
	vector<pii> par;

	MCMF(int N) : N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap), seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost)
	{
		this->cap[from][to]	 = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s)
	{
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0;
		ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator>		  its(N);
		q.push({0, s});

		auto relax = [&](int i, ll cap, ll cost, int dir)
		{
			ll val = di - pi[i] + cost;
			if (cap && val < dist[i])
			{
				dist[i] = val;
				par[i]	= {s, dir};
				if (its[i] == q.end())
					its[i] = q.push({-dist[i], i});
				else
					q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty())
		{
			s = q.top().second;
			q.pop();
			seen[s] = 1;
			di		= dist[s] + pi[s];
			for (int i : ed[s])
				if (!seen[i])
					relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (int i : red[s])
				if (!seen[i])
					relax(i, flow[i][s], -cost[i][s], 0);
		}
		rep(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t)
	{
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t])
		{
			ll fl = INF;
			for (int p, r, x = t; tie(p, r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p, r, x = t; tie(p, r) = par[x], x != s; x = p)
				if (r)
					flow[p][x] += fl;
				else
					flow[x][p] -= fl;
		}
		rep(i, 0, N) rep(j, 0, N) totcost += cost[i][j] * flow[i][j];
		return {totflow, totcost};
	}

	// If some costs can be negative, call this before maxflow:
	void setpi(int s)
	{ // (otherwise, leave this out)
		fill(all(pi), INF);
		pi[s]  = 0;
		int it = N, ch = 1;
		ll	v;
		while (ch-- && it--)
			rep(i, 0, N) if (pi[i] != INF) for (int to : ed[i]) if (cap[i][to]) if ((v = pi[i] + cost[i][to]) < pi[to])
				pi[to] = v,
				ch	   = 1;
		assert(it >= 0); // negative cost cycle
	}
};

int main()
{
	ll	p;
	int n, m;
	cin >> p >> n >> m;
	n += 3;
	vector<unordered_map<int, ll>> G(n);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		a += 3;
		b += 3;
		G[min(a, b)][max(a, b)]++;
	}
	G[0][1] = p;

	MCMF F(n);
	for (int v = 0; v < n; v++)
		for (auto [u, c] : G[v])
		{
			F.addEdge(v, u, c, 1);
			F.addEdge(u, v, c, 1);
		}

	auto [f, c] = F.maxflow(0, 2);
	if (f == p)
		cout << c - p;
	else
		cout << p - f << " people left behind";
}
