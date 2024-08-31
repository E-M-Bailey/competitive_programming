#include <bits/stdc++.h>

using namespace std;

int n, m, q;

int G[10][100000];
int ctr = 0;

struct T
{
	int cmp[20], col[20], cnt;
	constexpr T() : cmp{}, col{}, cnt(-1) {}
	T(int i)
	{
		col[n] = col[0] = G[0][i];
		cmp[n] = cmp[0] = ctr++;
		for (int j = 1; j < n; j++)
		{
			col[j + n] = col[j] = G[j][i];
			cmp[j + n] = cmp[j] = col[j] == col[j - 1] ? cmp[j - 1] : ctr++;
		}
		cnt = cmp[n - 1] - cmp[0] + 1;
	}
};

int P[1000000];
int find(int x)
{
	while (x != P[x])
		tie(x, P[x]) = pair{P[x], P[P[x]]};
	return x;
}

// segtree from KACTL
struct tree
{
	static constexpr T unit{};
	T				   f(T a, T b)
	{
		if (a.cnt < 0)
			return b;
		if (b.cnt < 0)
			return a;

		for (int i = 0; i < 2 * n; i++)
		{
			P[a.cmp[i]] = a.cmp[i];
			P[b.cmp[i]] = b.cmp[i];
		}
		T c{};
		c.cnt = a.cnt + b.cnt;
		for (int i = 0; i < n; i++)
			if (a.col[i + n] == b.col[i] && find(a.cmp[i + n]) != find(b.cmp[i]))
			{
				P[find(b.cmp[i])] = find(a.cmp[i + n]);
				c.cnt--;
			}
		for (int i = 0; i < n; i++)
		{
			c.col[i]	 = a.col[i];
			c.cmp[i]	 = find(a.cmp[i]);
			c.col[i + n] = b.col[i + n];
			c.cmp[i + n] = find(b.cmp[i + n]);
		}
		return c;
	}
	vector<T> s;
	int		  N;
	tree(int k = 0) : s(2 * k), N(k) {}
	void update(int pos, T val)
	{
		for (s[pos += N] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e)
	{
		T ra = unit, rb = unit;
		for (b += N, e += N; b < e; b /= 2, e /= 2)
		{
			if (b % 2)
				ra = f(ra, s[b++]);
			if (e % 2)
				rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> m >> q;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> G[i][j];
	tree tr(m);
	for (int j = 0; j < m; j++)
		tr.update(j, T(j));

	while (q--)
	{
		int l, r;
		cin >> l >> r;
		l--;
		cout << tr.query(l, r).cnt << '\n';
	}
}
