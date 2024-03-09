#include <bits/stdc++.h>

using namespace std;

int rd()
{
	static string s;
	cin >> s;
	int ans = 0;
	bool dec = false;
	int rd = 2;
	bool neg = false;
	for (char c : s)
	{
		if ('0' <= c && c <= '9')
		{
			ans = 10 * ans + c - '0';
			if (dec)
				rd--;
		}
		else if (c == '.')
			dec = true;
		else if (c == '-')
			neg = true;
	}
	while (rd--)
		ans *= 10;
	return neg ? -ans : ans;
}

int rup2(int x)
{
	x--;
	for (int i = 1; i < 32; i *= 2)
		x |= x >> i;
	return x + 1;
}

struct Tree
{
	int n;
	vector<int> S, L;
	void fix(int i)
	{
		if (i >= n)
			S[i] = 1;
		else
		{
			S[i] = 0;
			if (L[i * 2] == 0)
				S[i] += S[i * 2];
			if (L[i * 2 + 1] == 0)
				S[i] += S[i * 2 + 1];
		}
	}
	Tree(int N) : n(rup2(N)), S(2 * n), L(2 * n)
	{
		for (int i = 2 * n - 1; i > 0; i--)
			fix(i);
	}
	int qry(int l, int r, int nl, int nr, int i)
	{
		l = max(l, nl);
		r = min(r, nr);
		if (l >= r || L[i] > 0)
			return 0;
		if (l == nl && r == nr)
			return S[i];
		int nm = (nl + nr) / 2;
		return qry(l, r, nl, nm, 2 * i) + qry(l, r, nm, nr, 2 * i + 1);
	}
	void upd(int l, int r, int del, int nl, int nr, int i)
	{
		l = max(l, nl);
		r = min(r, nr);
		if (l >= r)
			return;
		//int old = S[i];
		if (l == nl && r == nr)
			L[i] += del;
		else
		{
			int nm = (nl + nr) / 2;
			upd(l, r, del, nl, nm, 2 * i);
			upd(l, r, del, nm, nr, 2 * i + 1);
		}
		fix(i);
		//cerr << l << ' ' << r << ' ' << del << ' ' << nl << ' ' << nr << ' ' << old << ' ' << S[i] << endl;
	}
	int qry(int l, int r)
	{
		return qry(l, r, 0, n, 1);
	}
	void upd(int l, int r, int del)
	{
		upd(l, r, del, 0, n, 1);
	}
};

struct rect
{
	int x1, y1, x2, y2;
};

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;
	vector<rect> Y(n);
	vector<vector<int>> S(200001), E(200001);
	for (int i = 0; i < n; i++)
	{
		Y[i].x1 = rd() + 100000;
		Y[i].y1 = rd() + 100000;
		Y[i].x2 = rd() + 100000;
		Y[i].y2 = rd() + 100000;
		S[Y[i].x1].push_back(i);
		E[Y[i].x2].push_back(i);
	}

	Tree tr(200001);

	long long ans = 0;

	for (int x = 0; x <= 200000; x++)
	{
		ans += 200001 - tr.qry(0, 200001);
		//if (x == 100001)
		//	cerr << 200001 - tr.qry(0, 200001) << endl;
		for (int i : S[x])
		{
			//cerr << x << ' ' << i << ' ' << Y[i].y1 << ' ' << Y[i].y2 << endl;
			tr.upd(Y[i].y1, Y[i].y2, 1);
		}
		for (int i : E[x])
			tr.upd(Y[i].y1, Y[i].y2, -1);
	}

	ans = (ans + 50) / 100;
	cout << ans / 100 << '.' << ans / 10 % 10 << ans % 10;
}