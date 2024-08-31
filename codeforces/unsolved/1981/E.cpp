#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

struct dso
{
	int			k;
	vector<int> R, P;
	dso(int n) : k(n), R(n), P(n)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = pair{P[x], P[P[x]]};
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
		R[x] += R[x] == R[y];
		P[y] = x;
		k--;
		return true;
	}
};

void go()
{
	int n;
	cin >> n;
	vector<tuple<int, int, int>> A(n);
	vector<pair<int, int>>		 Q;
	vector<tuple<int, int, int>> E;
	for (int i = 0; i < n; i++)
	{
		auto &[l, r, a] = A[i];
		cin >> l >> r >> a;
		Q.emplace_back(l, ~i);
		Q.emplace_back(r, i);
	}
	sort(begin(Q), end(Q));

	set<pair<int, int>> L;
	for (auto [t, i] : Q)
	{
		if (i < 0)
		{
			i		= ~i;
			int	 a	= get<2>(A[i]);
			auto it = L.emplace(a, i).first;
			if (it != begin(L))
				E.emplace_back(0, it->second, prev(it)->second);
			if (next(it) != end(L))
				E.emplace_back(0, it->second, next(it)->second);
		}
		else
		{
			int a = get<2>(A[i]);
			auto it = L.find({a, i});
			assert(it != end(L));
			it = L.erase(it);
			if (it != end(L) && it != begin(L))
				E.emplace_back(0, it->second, prev(it)->second);
		}
	}

	for (auto &[c, i, j] : E)
		c = abs(get<2>(A[i]) - get<2>(A[j]));
	sort(begin(E), end(E));

	long long ans = 0;
	dso		  D(n);
	for (auto [c, i, j] : E)
		if (D.onion(i, j))
			ans += c;

	cout << (D.k == 1 ? ans : -1) << '\n';
}
