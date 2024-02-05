#include <bits/stdc++.h>

using namespace std;

struct SuffixArray
{
	vector<int> sa, lcp;
	SuffixArray(string &s, int lim = 256)
	{
		int n = (int)size(s) + 1, k = 0, a, b;

		vector<int> x(begin(s), end(s) + 1), y(n), ws(max(n, lim)), rank(n);

		sa = lcp = y;
		iota(begin(sa), end(sa), 0);

		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p)
		{
			p = j;
			iota(begin(y), end(y), n - j);
			for (int i = 0; i < n; i++)
				if (sa[i] >= j)
					y[p++] = sa[i] - j;
			fill(begin(ws), end(ws), 0);
			for (int i = 0; i < n; i++)
				ws[x[i]]++;
			for (int i = 1; i < lim; i++)
				ws[i] += ws[i - 1];
			for (int i = n; i--;)
				sa[--ws[x[y[i]]]] = y[i];
			swap(x, y);
			p		 = 1;
			x[sa[0]] = 0;
			for (int i = 1; i < n; i++)
			{
				a	 = sa[i - 1];
				b	 = sa[i];
				x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
			}
		}
		for (int i = 1; i < n; i++)
			rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++)
			{
			}
	}
};

struct tree1
{
	int			n;
	vector<int> s;
	tree1(int k) : n(k), s(2 * k, INT_MIN) {}
	void upd(int pos, int val)
	{
		s[pos += n] = val;
		while (pos /= 2)
			s[pos] = max(s[pos * 2], s[pos * 2 + 1]);
	}
	int qry(int l, int r)
	{
		int a = INT_MIN, b = INT_MIN;
		for (l += n, r += n; l < r; l /= 2, r /= 2)
		{
			if (l % 2)
				a = max(a, s[l++]);
			if (r % 2)
				b = max(s[--r], b);
		}
		return max(a, b);
	}
	void reset()
	{
		fill(begin(s) + 1, end(s), INT_MIN);
	}
};
struct tree2
{
	int			n;
	vector<int> s;
	tree2(int k) : n(k), s(2 * k, INT_MAX) {}
	void upd(int pos, int val)
	{
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = min(s[pos * 2], s[pos * 2 + 1]);
	}
	int qry(int l, int r)
	{
		int a = INT_MAX, b = INT_MAX;
		for (l += n, r += n; l < r; l /= 2, r /= 2)
		{
			if (l % 2)
				a = min(a, s[l++]);
			if (r % 2)
				b = min(s[--r], b);
		}
		return min(a, b);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	string s;
	getline(cin, s);
	int n = (int)size(s);

	int N = n - 1;
	for (int i = 1; i < 32; i *= 2)
		N |= N >> i;
	N++;

	auto [p, lcp] = SuffixArray(s);
	p.erase(begin(p));
	lcp.erase(begin(lcp));
	vector<int> q(n);
	for (int i = 0; i < n; i++)
		q[p[i]] = i;

	tree1		T1(N);
	tree2		T2(N);
	vector<int> L(n), R(n);
	for (int i = 0; i < n; i++)
	{
		L[p[i]] = T1.qry(0, p[i]);
		T1.upd(p[i], i);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		R[p[i]] = T2.qry(0, p[i]);
		T2.upd(p[i], i);
	}

	tree2 rmq(N);
	for (int i = 0; i < n; i++)
		rmq.upd(i, lcp[i]);

	vector<vector<pair<int, int>>> G(n);
	for (int i = 0; i < n; i++)
		G[i].emplace_back(i + 1, 1);
	for (int i = 0; i < n; i++)
	{
		int l = L[p[i]], r = R[p[i]];
		int d = -1;
		if (l >= 0)
		{
			int a = rmq.qry(l + 1, i + 1);
			d	  = max(a, d);
		}
		if (r < n)
		{
			int a = rmq.qry(i + 1, r + 1);
			d	  = max(a, d);
		}
		if (d >= 0)
			G[p[i]].emplace_back(d + p[i], 3);
	}

	vector<int> DP(n + 1, INT_MAX / 2);
	DP[0] = 0;
	for (int i = 0; i < n; i++)
		for (auto [j, d] : G[i])
			DP[j] = min(DP[j], DP[i] + d);
	cout << DP[n];
}
