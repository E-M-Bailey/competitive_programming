#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

vector<int>				X;
unordered_map<int, int> XX;

struct T
{
	int			n;
	vector<int> s, z;
	T(int N) : n(N), s(2 * N), z(2 * N) {}
	void u(int l, int r, int L, int R, int i, int d)
	{
		if ((l = max(l, L)) < (r = min(r, R)))
		{
			if (l == L && r == R)
				z[i] += d;
			else
			{
				u(l, r, L, (L + R) / 2, i * 2, d);
				u(l, r, (L + R) / 2, R, i * 2 + 1, d);
			}
			s[i] = z[i] ? X[R] - X[L] : i >= n ? 0 : s[i * 2] + s[i * 2 + 1];
		}
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int q, w;
	cin >> q >> w;
	unordered_map<int, unordered_set<int>> S;
	vector<tuple<int, int, int>>		   Q(q);
	for (auto &[l, r, d] : Q)
	{
		int x, y;
		cin >> x >> y;
		auto [it, i] = S[x].insert(y);
		if (!i)
			S[x].erase(it);
		d = i ? 1 : -1;
		X.push_back(l = max(0, x - y));
		X.push_back(r = min(w, x + y));
	}
	sort(begin(X), end(X));
	X.erase(unique(begin(X), end(X)), end(X));
	int n = (int)size(X) - 1;
	for (int i = 0; i <= n; i++)
		XX[X[i]] = i;
	for (int i = 1; i < 32; i *= 2)
		n |= n >> 1;
	n++;
	while ((int)size(X) <= n)
		X.push_back(w);

	T t(n);
	for (auto [l, r, d] : Q)
	{
		t.u(XX[l], XX[r], 0, n, 1, d);
		cout << fixed << setprecision(8) << t.s[1] * sqrt(2) << '\n';
	}
}
