#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, R;
	dso(int n) : P(n), R(n)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = pair{ P[x], P[P[x]] };
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
		return true;
	}
	void reset(int n)
	{
		iota(begin(P), begin(P) + n, 0);
		fill(begin(R), begin(R) + n, 0);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	vector<tuple<int, int, int>> E;
	vector<pair<int, int>> T;
	dso D(20000);
	E.reserve(30000);
	T.reserve(19999);
	cin >> n >> m;
	for (;;)
	{
		dso D(n);
		E.resize(m);
		T.clear();
		for (auto &[u, v, w] : E)
			cin >> u >> v >> w;
		sort(begin(E), end(E), [](tuple<int, int, int> a, tuple<int, int, int> b) { return get<2>(a) < get<2>(b); });
		int64_t c = 0;
		for (auto [u, v, w] : E)
			if (D.onion(u, v))
			{
				c += w;
				T.push_back(minmax(u, v));
			}
		if ((int)T.size() < n - 1)
			cout << "Impossible\n";
		else
		{
			cout << c << '\n';
			sort(begin(T), end(T));
			for (auto [u, v] : T)
				cout << u << ' ' << v << '\n';
		}

		int pr = n;
		cin >> n >> m;
		if (n)
			D.reset(pr);
		else
			break;
	}
}
