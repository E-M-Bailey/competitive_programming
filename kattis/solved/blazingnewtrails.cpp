#include <bits/stdc++.h>

using namespace std;

int n, m, k, w;

struct edge
{
	int u, v;
	int64_t c;
	friend bool operator<(edge const &a, edge const &b)
	{
		return a.c < b.c;
	}
};

vector<edge> E0, E1;
int a, b;

struct dso
{
	int k;
	vector<int> R, P;

	dso() :
		R(n),
		P(n)
	{
		reset();
	}

	int find(int x)
	{
		while (P[x] != x)
			tie(x, P[x]) = make_pair(P[x], P[P[x]]);
		return x;
	}

	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (R[x] < R[y])
			swap(x, y);
		P[y] = x;
		R[x] += R[x] == R[y];
		k--;
		return true;
	}

	void reset()
	{
		fill(begin(R), end(R), 0);
		iota(begin(P), end(P), 0);
		k = n;
	}
};

pair<int64_t, int> solve(int64_t lam)
{
	static dso D;
	D.reset();

	int64_t cst = 0;
	int ct = 0;

	int i = 0, j = 0;
	while ((i < a || j < b) && D.k > 1)
	{
		if (j == b || (i < a && E0[i].c <= E1[j].c + lam))
		{
			if (D.onion(E0[i].u, E0[i].v))
				cst += E0[i].c;
			i++;
		}
		else
		{
			if (D.onion(E1[j].u, E1[j].v))
			{
				cst += E1[j].c + lam;
				ct++;
			}
			j++;
		}
	}

	if (D.k > 1)
		ct = -1;
	return { cst, ct };
}

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin >> n >> m >> k >> w;

	vector<bool> S(n);
	for (int i = 0; i < k; i++)
	{
		int s;
		cin >> s;
		S[s - 1] = true;
	}

	E0.reserve(m);
	E1.reserve(m);
	for (int i = 0; i < m; i++)
	{
		int u, v, c;
		cin >> u >> v >> c;
		u--;
		v--;
		bool sp = S[u] ^ S[v];
		(sp ? E1 : E0).push_back(edge{ u, v, c });
	}
	sort(begin(E0), end(E0));
	sort(begin(E1), end(E1));
	a = (int)E0.size();
	b = (int)E1.size();

	int64_t lo = -3e5, hi = 3e5, ans = INT64_MAX;

	auto [c0, ct0] = solve(lo);
	if (ct0 < w)
	{
		cout << -1;
		return 0;
	}
	tie(c0, ct0) = solve(hi);
	if (ct0 > w)
	{
		cout << -1;
		return 0;
	}

	while (lo < hi)
	{
		int64_t lam = lo + (hi - lo) / 2;
		auto [c, ct] = solve(lam);
		if (ct > w)
			lo = lam + 1;
		else
		{
			hi = lam;
			ans = c - w * lam;
		}
	}
	cout << ans;
}