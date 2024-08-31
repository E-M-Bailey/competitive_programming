#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

int64_t inv_ct(vector<int> &P, int l, int r)
{
	if (r - l <= 1)
		return 0;

	int		m	= (l + r) / 2;
	int64_t ans = inv_ct(P, l, m) + inv_ct(P, m, r);

	vector<int> P2;
	P2.reserve(r - l);
	int a = l, b = m;
	while (a < m && b < r)
	{
		if (P[a] < P[b])
			P2.push_back(P[a++]);
		else
		{
			ans += m - a;
			P2.push_back(P[b++]);
		}
	}
	while (a < m)
		P2.push_back(P[a++]);
	while (b < m)
		P2.push_back(P[b++]);

	copy(begin(P2), end(P2), begin(P) + l);
	return ans;
}

int ct_lt(vector<vector<int>> const &mst, int x, int l, int r, int ni, int nl, int nr)
{
	l = max(l, nl);
	r = min(r, nr);
	if (l >= r)
		return 0;

	auto &row = mst[ni];
	if (l == nl && r == nr)
	{
		auto it = begin(row) + nl, jt = begin(row) + nr;
		return int(lower_bound(it, jt, x) - it);
	}

	int nm = (nl + nr) / 2;
	return ct_lt(mst, x, l, r, ni + 1, nl, nm) + ct_lt(mst, x, l, r, ni + 1, nm, nr);
}

int ct_lt(vector<vector<int>> const &mst, int x, int l, int r)
{
	return ct_lt(mst, x, l, r, 0, 0, (int)size(mst[0]));
}

void invert(vector<int> &P)
{
	int			n = (int)size(P);
	vector<int> Q(n);
	for (int i = 0; i < n; i++)
		Q[P[i]] = i;
	P = move(Q);
}

void go()
{
	int		n;
	int64_t k;
	cin >> n >> k;
	vector<int> P(n);
	for (int &p : P)
	{
		cin >> p;
		p--;
	}
	invert(P);

	vector<int> P2 = P;
	k -= inv_ct(P2, 0, n);
	if (k % 2)
	{
		cout << "NO\n";
		return;
	}

	int N = n - 1;
	for (int i = 1; i < 32; i *= 2)
		N |= N >> i;
	N++;

	vector<vector<int>> mst(1, vector<int>(N, INT_MAX));
	copy(begin(P), end(P), begin(mst.back()));
	for (int s = 1; s < N; s *= 2)
	{
		vector<int> &A = mst.back(), B(N);
		for (int i = 0; i < N; i += 2 * s)
			merge(begin(A) + i, begin(A) + i + s, begin(A) + i + s, begin(A) + i + 2 * s, begin(B) + i);
		mst.push_back(move(B));
	}
	reverse(begin(mst), end(mst));
	int m = (int)size(mst);

	vector<int> Q(n);

	int offset = 0;
	for (int i = n; i-- > 0;)
	{
		int cur = P[i];
		int mx	= 2 * ct_lt(mst, cur, 0, i);
		if (mx <= k)
		{
			k -= mx;
			Q[i] = offset++;
			continue;
		}

		int l = 0, r = i;
		int64_t k2 = k;
		while (l < r)
		{
			int m = (l + r) / 2;
			int amt = 2 * ct_lt(mst, cur, m, i);
			if (amt > k)
				l = m + 1;
			else
			{
				k2 = k - amt;
				r = m;
			}
		}
		k = k2;
		Q[i] = offset + l;
		for (int j = 0; j < i; j++)
			Q[j] = offset + (j >= l) + j;
		break;
	}

	if (k)
	{
		cout << "NO\n";
		return;
	}

	//invert(Q);
	cout << "YES\n";
	for (int q : Q)
		cout << q + 1 << ' ';
	cout << '\n';
}
