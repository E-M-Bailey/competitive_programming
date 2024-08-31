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
	// cin >> tc;
	while (tc--)
		go();
}

struct tree
{
	vector<pair<long long, long long>> s;
	vector<long long>				   z;
	int								   n;
	tree(int N) : s(2 * N), z(2 * N), n(N) {}
	void pu(int i, int nl, int nr)
	{
		if (z[i])
		{
			s[i].first	= (long long)z[i] * (nr - nl);
			s[i].second = z[i];
			if (i < n)
			{
				z[i * 2]	 = z[i];
				z[i * 2 + 1] = z[i];
			}
			z[i] = 0;
		}
	}
	pair<long long, long long> qry(int l, int r, int nl, int nr, int i)
	{
		l = max(l, nl);
		r = min(r, nr);
		if (l >= r)
			return {0, INT_MAX};
		pu(i, nl, nr);
		if (l == nl && r == nr)
			return s[i];
		int md		  = (nl + nr) / 2;
		auto [s1, m1] = qry(l, r, nl, md, i * 2);
		auto [s2, m2] = qry(l, r, md, nr, i * 2 + 1);
		return {s1 + s2, min(m1, m2)};
	}
	pair<long long, long long> qry(int l, int r)
	{
		return qry(l, r, 0, n, 1);
	}
	void upd(int l, int r, int nl, int nr, int i, long long d)
	{
		l = max(l, nl);
		r = min(r, nr);
		if (l == nl && r == nr)
		{
			z[i] = d;
			pu(i, nl, nr);
			return;
		}
		pu(i, nl, nr);
		if (l >= r)
			return;
		pu(i, nl, nr);
		int md = (nl + nr) / 2;
		upd(l, r, nl, md, i * 2, d);
		upd(l, r, md, nr, i * 2 + 1, d);
		s[i].first	= s[i * 2].first + s[i * 2 + 1].first;
		s[i].second = s[i * 2 + 1].second;
	}
	void upd(int l, int r, long long d)
	{
		upd(l, r, 0, n, 1, d);
	}

	int first_le(int l, int nl, int nr, int i, long long y)
	{
		while (i < n)
		{
			int md = (nl + nr) / 2;
			pu(i * 2, nl, md);
			if (l >= md || s[i * 2].second > y)
			{
				pu(i * 2 + 1, md, nr);
				nl = md;
				i  = i * 2 + 1;
			}
			else
			{
				nr = md;
				i *= 2;
			}
		}
		return i - n;
	}
	int first_le(int l, long long y)
	{
		pu(1, 0, n);
		return l != n && s[1].second <= y ? first_le(l, 0, n, 1, y) : n;
	}

	int sum_le(int nl, int nr, int i, long long y)
	{
		while (i < n)
		{
			int md = (nl + nr) / 2;
			pu(i * 2, nl, md);
			if (s[i * 2].first <= y)
			{
				pu(i * 2 + 1, md, nr);
				nl = md;
				y -= s[i * 2].first;
				i  = i * 2 + 1;
			}
			else
			{
				nr = md;
				i *= 2;
			}
		}
		return i - n;
	}
	int sum_le(long long y)
	{
		pu(1, 0, n);
		return s[1].first <= y ? n : sum_le(0, n, 1, y);
	}
};

void go()
{
	int n, q;
	cin >> n >> q;
	int N = n - 1;
	for (int i = 1; i < 32; i *= 2)
		N |= n >> i;
	N++;
	tree T(N);
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		T.upd(i, i + 1, a);
	}

	while (q--)
	{
		int		  c, x;
		long long y;
		cin >> c >> x >> y;
		if (c == 1)
		{
			int z = T.first_le(0, y);
			if (z < x)
				T.upd(z, x, y);
		}
		else
		{
			x--;
			int ans = 0;
			while (x < n)
			{
				int w = min(n, T.first_le(x, y));
				int z = min(n, T.sum_le(y + T.qry(0, w).first));
				ans += z - w;
				y -= T.qry(w, z).first;
				x = z;
			}
			cout << ans << '\n';
		}
	}
}
