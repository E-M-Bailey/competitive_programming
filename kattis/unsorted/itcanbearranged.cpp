#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define sz(C) int(size(C))
#define rep(i, a, b) for (int i = a; i < b; i++)

struct PushRelabel
{
	struct Edge
	{
		int dest, back;
		ll f, c;
	};
	vector<vector<Edge>> g;
	vector<ll> ec;
	vector<Edge *> cur;
	vector<vi> hs;
	vi H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}

	void addEdge(int s, int t, ll cap, ll rcap = 0)
	{
		if (s == t) return;
		g[s].push_back({ t, sz(g[t]), 0, cap });
		g[t].push_back({ s, sz(g[s]) - 1, 0, rcap });
	}

	void addFlow(Edge &e, ll f)
	{
		Edge &back = g[e.dest][e.back];
		if (!ec[e.dest] && f)
			hs[H[e.dest]].push_back(e.dest);
		e.f += f;
		e.c -= f;
		ec[e.dest] += f;
		back.f -= f;
		back.c += f;
		ec[back.dest] -= f;
	}

	ll calc(int s, int t)
	{
		int v = sz(g);
		H[s] = v;
		ec[t] = 1;
		vi co(2 * v);
		co[0] = v - 1;
		rep(i, 0, v)
			cur[i] = g[i].data();
		for (Edge &e : g[s]) addFlow(e, e.c);

		for (int hi = 0;;)
		{
			while (hs[hi].empty())
				if (!hi--)
					return -ec[s];
			int u = hs[hi].back();
			hs[hi].pop_back();
			while (ec[u] > 0)
				if (cur[u] == g[u].data() + sz(g[u]))
				{
					H[u] = 1e9;
					for (Edge &e : g[u])
						if (e.c && H[u] > H[e.dest] + 1)
							H[u] = H[e.dest] + 1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						rep(i, 0, v)
						if (hi < H[i] && H[i] < v)
							--co[H[i]], H[i] = v + 1;
					hi = H[u];
				}
				else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
					addFlow(*cur[u], min(ec[u], cur[u]->c));
				else
					++cur[u];
		}
	}
};

int main()
{
	int tc;
	cin >> tc;
	for (int tt = 1; tt <= tc; tt++)
	{
		cout << "Case " << tt << ": ";

		int n, m;
		cin >> n >> m;
		vi A(n), B(n), S(n);
		rep(i, 0, n)
		{
			cin >> A[i] >> B[i] >> S[i];
			S[i] = (S[i] + m - 1) / m;
		}
		vector<vi> G(n);
		rep(i, 0, n)
			rep(j, 0, n)
		{
			int clean;
			cin >> clean;
			if (B[i] + clean < A[j])
				G[i].push_back(j);
		}

		int lo = 0, hi = accumulate(begin(S), end(S), 0);
		while (lo < hi)
		{
			int mid = (lo + hi) / 2;
			PushRelabel PR(2 * n + 5);
			int s = 2 * n, a = s + 1, t = a + 1, sp = t + 1, tp = sp + 1;

			PR.addEdge(s, a, mid);
			PR.addEdge(t, s, mid);
			rep(i, 0, n)
			{
				int u = i * 2, v = u + 1;
				PR.addEdge(a, u, mid);
				PR.addEdge(u, v, mid);
				PR.addEdge(v, t, mid);
				PR.addEdge(u, tp, S[i]);
				PR.addEdge(sp, v, S[i]);
				for (int j : G[i])
				{
					int w = j * 2;
					PR.addEdge(v, w, mid);
				}
			}

			PR.calc(sp, tp);
			bool good = true;
			rep(i, 0, n)
				good &= PR.g[sp][i].c == 0;
			if (good)
				hi = mid;
			else
				lo = mid + 1;
		}
		cout << lo << '\n';
	}
}