#include <bits/stdc++.h>

using namespace std;

int n;
int G[100];
int A[100][100], B[100][100], C[100][100];
int DP1[100][100][100], DP2[100][100][100];
int ans[100][100];

struct pt
{
	int x, y, i;
	pt(int X = 0, int Y = 0) : x(X), y(Y), i(X * n + Y) {}
	friend bool operator<(const pt &l, const pt &r)
	{
		if (l.x != r.x)
			return l.x < r.x;
		return l.y < r.y;
	}
	friend bool operator>(const pt &l, const pt &r)
	{
		if (l.x != r.x)
			return l.x > r.x;
		return l.y > r.y;
	}
	friend bool operator<=(const pt &l, const pt &r)
	{
		return !(l > r);
	}
	friend bool operator>=(const pt &l, const pt &r)
	{
		return !(l < r);
	}
	friend bool operator==(const pt &l, const pt &r)
	{
		return l.x == r.x && l.y == r.y;
	}
	friend bool operator!=(const pt &l, const pt &r)
	{
		return !(l == r);
	}
	friend pt operator-(const pt &a, const pt &b)
	{
		return {a.x - b.x, a.y - b.y};
	}
	friend int operator*(const pt &a, const pt &b)
	{
		return a.x * b.x + a.y * b.y;
	}
	friend int operator^(const pt &a, const pt &b)
	{
		return a.x * b.y - a.y * b.x;
	}
	pt &operator++()
	{
		if (++y == n)
		{
			y = 0;
			++x;
		}
		++i;
		return *this;
	}
	pt &operator--()
	{
		if (--y < 0)
		{
			y = n - 1;
			--x;
		}
		--i;
		return *this;
	}
	pt nxt() const
	{
		pt nx = *this;
		return ++nx;
	}
	pt fl() const
	{
		return pt{n - 1 - x, n - 1 - y};
	}
	operator int() const
	{
		return i;
	}
	bool operator!() const
	{
		return x == 0 && y == 0;
	}
	friend ostream &operator<<(ostream &os, const pt &p)
	{
		return os << '(' << p.x << ',' << p.y << ')';
	}
};

void solve(int DP[100][100][100])
{
	for (pt a = 0; a.x < n; ++a)
		for (pt b = a; b.x < n; ++b)
		{
			A[a][b] = B[a][b] = C[a][b] = 0;
			for (pt c{a.x, 0}; c.x <= b.x; ++c)
			{
				int cp = (b - a) ^ (c - a);
				if (a.x == b.x)
					cp = c.y < a.y ? -1 : c.y <= b.y ? 0 : 1;
				(cp < 0 ? A : cp == 0 ? B : C)[a][b] += G[c];
			}
		}

	for (pt a = 0; a.x < n; ++a)
		for (pt b = a; b.x < n; ++b)
			DP1[a][b][b] = DP2[a][b][b] = 0;

	for (pt a{n - 1, n - 1}; a.x >= 0; --a)
		for (pt b{n - 1, n - 1}; b >= a; --b)
			for (pt z{n - 1, n - 1}; z > b; --z)
			{
				pt	 db = a == b ? pt{0, 1} : b - a;
				pt	 dz = z - b;
				int &dp = DP[a][b][z];
				dp		= INT_MIN;
				for (pt c = b.nxt(); c <= z; ++c)
				{
					pt dc = c - b;
					if ((db ^ dc) <= 0 && (dz ^ dc) >= 0)
						dp = max(dp, DP[b][c][z]);
				}
				if (dp > INT_MIN)
					dp += A[a][b] + B[a][b] + A[b][z] + B[b][z] - A[b][b] - B[b][b] - A[a][z] - B[a][z];
			}
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n;
		for (pt a = 0; a.x < n; ++a)
		{
			bool g;
			cin >> g;
			G[a] = g ? 1 : -1;
		}

		solve(DP1);

		for (pt a = 0; a.x < n; ++a)
			if (a < a.fl())
				swap(G[a], G[a.fl()]);

		solve(DP2);

		int best = 0;
		for (pt a = 0; a.x < n; ++a)
			for (pt b = a; b.x < n; ++b)
				best = max(best, B[b.fl()][a.fl()] + DP1[a][a][b] + DP2[b.fl()][b.fl()][a.fl()]);
		cout << best << '\n';
	}
}
