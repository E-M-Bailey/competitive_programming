#include <bits/stdc++.h>

using namespace std;

typedef int64_t i64;

int rup2(int x)
{
	x--;
	for (int i = 1; i < 32; i *= 2)
		x |= x >> i;
	return x + 1;
}

struct Tree
{
	int					n, m;
	vector<vector<i64>> S, L;
	Tree(int N) : n(rup2(N))
	{
		S.emplace_back(n);
		L.emplace_back(n, -1);
		while (S.back().size() > 1)
		{
			L.emplace_back(S.back().size() / 2, -1);
			S.emplace_back(S.back().size() / 2);
		}
		m = size(S);
	}

	void pd(int i, int j)
	{
		if (L[i][j] < 0)
			return;
		if (i > 0)
		{
			L[i - 1][j * 2]		= L[i][j];
			L[i - 1][j * 2 + 1] = L[i][j];
		}
		S[i][j] = L[i][j];
		L[i][j] = -1;
	}

	i64 query(int lo, int hi, int nlo, int nhi, int i, int j)
	{
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (hi <= lo)
			return 0;
		pd(i, j);
		if (lo == nlo && hi == nhi)
			return S[i][j];
		int mid = (nlo + nhi) / 2;
		return max(query(lo, hi, nlo, mid, i - 1, j * 2), query(lo, hi, mid, nhi, i - 1, j * 2 + 1));
	}

	i64 query(int lo, int hi)
	{
		return query(lo, hi, 0, n, m - 1, 0);
	}

	void update(int lo, int hi, int nlo, int nhi, int i, int j, i64 val)
	{
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (hi <= lo)
			return;
		pd(i, j);
		if (lo == nlo && hi == nhi)
		{
			S[i][j] = L[i][j] = val;
			return;
		}
		int mid = (nlo + nhi) / 2;
		update(lo, hi, nlo, mid, i - 1, j * 2, val);
		update(lo, hi, mid, nhi, i - 1, j * 2 + 1, val);
		S[i][j] = max({S[i][j], S[i - 1][j * 2], S[i - 1][j * 2 + 1]});
	}

	void update(int lo, int hi, i64 val)
	{
		return update(lo, hi, 0, n, m - 1, 0, val);
	}
};

int main()
{
	int n;
	cin >> n;

	set<i64>			   X;
	vector<pair<i64, i64>> Q(n);
	for (auto &[x, y] : Q)
	{
		cin >> x >> y;
		y += x;
		X.insert(x);
		X.insert(y);
	}

	vector<i64>				ICC(begin(X), end(X));
	int						k = size(ICC);
	unordered_map<i64, int> CC;
	for (int i = 0; i < k; i++)
		CC.emplace(ICC[i], i);

	Tree T(k);

	i64 h = 0;

	for (auto [x, y] : Q)
	{
		i64 s  = y - x;
		i64 ht = T.query(CC[x], CC[y]);
		T.update(CC[x], CC[y], ht + s);
		h = max(h, ht + s);
		cout << h << '\n';
	}
}
