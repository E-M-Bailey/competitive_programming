#include <bits/stdc++.h>

using namespace std;

constexpr int64_t MOD = 1'000'000'007;

int rup2(int x)
{
	--x;
	for (int i = 1; i < 32; i *= 2)
		x |= x >> i;
	return x + 1;
}

struct cubic
{
	array<int, 4> C{};
	constexpr cubic(int a = 0, int b = 0, int c = 0, int d = 0) : C{a, b, c, d} {}
	constexpr int operator()(int x) const
	{
		int y = 0;
		for (int i = 3; i >= 0; i--)
			y = (C[i] + (int64_t)x * y) % MOD;
		return y;
	}
	constexpr int sum(int hi) const
	{
		int64_t a = hi, b = a * (a - 1) / 2 % MOD, c = a * (a - 1) * (2 * a - 1) / 6 % MOD, d = b * b % MOD;
		return (a * C[0] + b * C[1] + c * C[2] + d * C[3]) % MOD;
	}
	constexpr int sum(int lo, int hi) const
	{
		return (sum(hi) - sum(lo) + MOD) % MOD;
	}
	constexpr cubic &operator+=(const cubic &b)
	{
		for (int i = 0; i < 4; i++)
			C[i] = (C[i] + b.C[i]) % MOD;
		return *this;
	}
	constexpr cubic operator+(const cubic &b) const
	{
		return cubic(*this) += b;
	}
	constexpr cubic &operator*=(int b)
	{
		for (int i = 0; i < 4; i++)
			C[i] = (C[i] * (int64_t)b) % MOD;
		return *this;
	}
	constexpr cubic operator*(int b) const
	{
		return cubic(*this) *= b;
	}
};
constexpr cubic unit{};
constexpr cubic operator+(const cubic &a, const cubic &b)
{
	return cubic(a) += b;
}
struct tree
{
	int					  n, m;
	vector<vector<int>>	  s;
	vector<vector<cubic>> l;
	tree(vector<int> &&lv) : n(rup2(size(lv)))
	{
		s.push_back(forward<vector<int>>(lv));
		s.back().resize(n, 0);
		l.emplace_back(n, unit);
		while (size(s.back()) > 1)
		{
			vector<int> L(size(s.back()) / 2);
			for (int i = 0; i < size(L); i++)
				L[i] = (s.back()[i * 2] + s.back()[i * 2 + 1]) % MOD;
			l.emplace_back(size(L), unit);
			s.push_back(move(L));
		}
		m = size(s);
	}
	int get(int i, int j, int nlo, int nhi)
	{
		return (s[i][j] + l[i][j].sum(nlo, nhi)) % MOD;
	}
	void pd(int i, int j, int nlo, int nhi)
	{
		if (i)
		{
			l[i - 1][j * 2] += l[i][j];
			l[i - 1][j * 2 + 1] += l[i][j];
		}
		s[i][j] = get(i, j, nlo, nhi);
		l[i][j] = 0;
	}
	int query(int lo, int hi, int nlo, int nhi, int i, int j)
	{
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (hi <= lo)
			return 0;
		if (lo == nlo && hi == nhi)
			return get(i, j, nlo, nhi);
		pd(i, j, nlo, nhi);
		int mid = (nlo + nhi) / 2;
		int ans = (query(lo, hi, nlo, mid, i - 1, j * 2) + query(lo, hi, mid, nhi, i - 1, j * 2 + 1)) % MOD;
		return ans;
	}
	int query(int lo, int hi)
	{
		return query(lo, hi, 0, n, m - 1, 0);
	}
	void update(int lo, int hi, int nlo, int nhi, int i, int j, const cubic &f)
	{
		lo = max(lo, nlo);
		hi = min(hi, nhi);
		if (hi <= lo)
			return;
		pd(i, j, nlo, nhi);
		if (lo == nlo && hi == nhi)
		{
			l[i][j] += f;
			return;
		}
		s[i][j] = (s[i][j] + f.sum(lo, hi)) % MOD;
		int mid = (nlo + nhi) / 2;
		update(lo, hi, nlo, mid, i - 1, j * 2, f);
		update(lo, hi, mid, nhi, i - 1, j * 2 + 1, f);
	}
	void update(int lo, int hi, const cubic &f)
	{
		update(lo, hi, 0, n, m - 1, 0, f);
	}
};
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	tree T(vector<int>(n, 0));
	while (m--)
	{
		int t, x, y;
		cin >> t >> x >> y;
		x--;
		if (t == 0)
			cout << T.query(x, y) << '\n';
		else
		{
			int64_t a = (MOD + 1 - x) % MOD, b = (MOD + 2 - x) % MOD, c = (MOD + 3 - x) % MOD;
			cubic	f(a * b % MOD * c % MOD, (a * b + a * c + b * c) % MOD, (a + b + c) % MOD, 1);
			if (t == 2)
				f *= MOD - 1;
			T.update(x, y, f);
		}
	}
}
