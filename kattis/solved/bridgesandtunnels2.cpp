#include <bits/stdc++.h>

using namespace std;

struct edge
{
	int		u, v;
	int64_t wo, wi;
};

struct entry
{
	int		v;
	int64_t wo, wi;
	entry(int v, int64_t wo, int64_t wi) : v(v), wo(wo), wi(wi) {}
	pair<int64_t, int64_t> w()
	{
		return {wo, wi};
	}
};

bool operator<(const entry &l, const entry &r)
{
	return tie(l.wo, l.wi) > tie(r.wo, r.wi);
}

entry &operator+=(entry &l, const entry &r)
{
	l.wo += r.wo;
	l.wi += r.wi;
	return l;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m, p;
	cin >> n >> m >> p;
	vector<edge> E(m);
	for (auto &[u, v, wo, wi] : E)
	{
		cin >> u >> v;
		int64_t w;
		cin >> w;
		char c;
		cin >> c;
		(c == 'O' ? wo : wi) = w;
	}

	vector<vector<entry>> G(n);
	for (auto [u, v, wo, wi] : E)
	{
		G[u].emplace_back(v, wo, wi);
		G[v].emplace_back(u, wo, wi);
	}
	E.clear();

	priority_queue<entry>		   PQ;
	vector<pair<int64_t, int64_t>> D(n);
	for (int i = 0; i < p; i++)
	{
		int s, t;
		cin >> s >> t;

		fill(begin(D), end(D), pair<int64_t, int64_t>{INT64_MAX, INT64_MAX});

		PQ.emplace(s, 0, 0);
		while (!PQ.empty())
		{
			auto ev = PQ.top();
			PQ.pop();
			if (ev.w() >= D[ev.v])
				continue;
			D[ev.v] = ev.w();
			for (auto ew : G[ev.v])
				if (D[ew.v].first == INT64_MAX)
					PQ.push(ew += ev);
		}
		auto [x, y] = D[t];
		if (x == INT64_MAX)
			cout << "IMPOSSIBLE\n";
		else
			cout << x << ' ' << x + y << '\n';
	}
}
