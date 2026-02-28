#include <bits/extc++.h>

using namespace std;

// using ll = long long;

static constexpr int P = 998244353;

template<typename C, integral T = int>
[[nodiscard]] static constexpr int sz(const C& c) noexcept
{
	return static_cast<T>(size(c));
}

struct dso
{
	vector<int> S, P;
	int k;
	dso(int n) : S(n, 1), P(n), k{ n }
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (P[x] != x)
			tie(x, P[x]) = pair{ P[x], P[P[x]] };
		return x;
	}
	int onion(int x, int y)
	{
		// x = find(x);
		// y = find(y);
		if (x == y)
			return x;
		if (S[x] < S[y])
			swap(x, y);
		S[x] += S[y];
		P[y] = x;
		--k;
		return x;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>> E(m);
	for (auto &[u, v] : E)
	{
		cin >> u >> v;
		--u;
		--v;
	}
	int c = 0;
	dso D(n);
	while (!E.empty())
	{
		auto [u, v] = E.back();
		E.pop_back();
		u = D.find(u);
		v = D.find(v);
		bool a = D.k > 2 || u == v;
		if (a)
			D.onion(u, v);
		if ((c = c * 2 + !a) >= P)
			c -= P;
	}
	if ((c *= 2) >= P)
		c -= P;
	cout << c;
}
