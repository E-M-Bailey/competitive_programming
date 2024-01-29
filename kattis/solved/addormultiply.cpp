#include <bits/stdc++.h>

using namespace std;

long long constexpr MOD = 1000000007;

int mdiv(int num, int den)
{
	int x = 0, u = MOD, y = 1, v = den;
	while (v)
	{
		int q = u / v;
		int z = x - y * q, w = u - v * q;
		u = v;
		v = w;
		x = y;
		y = z;
	}
	if (x < 0)
		x += MOD;
	return int((long long)x * num % MOD);
}

// Source: KACTL
struct bit
{
	vector<int> s;
	bit(int n) : s(n, 1) {}
	void update(int pos, long long ratio)
	{
		for (; pos < (int)size(s); pos |= pos + 1)
			s[pos] = int(s[pos] * ratio % MOD);
	}
	int query(int pos)
	{
		long long res = 1;
		for (; pos > 0; pos &= pos - 1)
			res = res * s[pos - 1] % MOD;
		return (int)res;
	}
	int query(int l, int r)
	{
		return mdiv(query(r), query(l));
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	bit T(n);
	set<int> P{0, n}, Q{0, n};
	string s;
	cin >> s;
	vector<int> A(n);
	int a = 0, b = 0;

	{
		vector<bool> B(n);
		for (int i = 0; i < n; i++)
		{
			A[i] = s[i * 2] - '0';
			T.update(i, A[i]);
		}
		int cura = A[0], curb = A[0];
		for (int i = 1; i < n; i++)
		{
			bool plus = s[i * 2 - 1] == '+';
			if (plus)
			{
				P.insert(i);
				a = (a + cura) % MOD;
				cura = A[i];
				curb = int((long long)curb * A[i] % MOD);
			}
			else
			{
				Q.insert(i);
				b = (b + curb) % MOD;
				curb = A[i];
				cura = int((long long)cura * A[i] % MOD);
			}
		}
		a = (a + cura) % MOD;
		b = (b + curb) % MOD;
	}

	auto const toggle = [&](int i, int &c, set<int> &R)
	{
		set<int>::const_iterator it = R.lower_bound(i);
		if (*it == i)
		{
			// + -> *
			int l = *prev(it), r = *R.erase(it);
			c -= T.query(l, i);
			if (c < 0)
				c += MOD;
			c -= T.query(i, r);
			if (c < 0)
				c += MOD;
			c += T.query(l, r);
			if (c >= MOD)
				c -= MOD;
		}
		else
		{
			// * -> +
			int l = *prev(it), r = *it;
			R.insert(it, i);
			c += T.query(l, i);
			if (c >= MOD)
				c -= MOD;
			c += T.query(i, r);
			if (c >= MOD)
				c -= MOD;
			c -= T.query(l, r);
			if (c < 0)
				c += MOD;
		}
	};

	auto const set_val = [&](int i, int ratio, int &c, set<int> const &R)
	{
		auto it = R.upper_bound(i);
		int l = *prev(it), r = *it;
		int q = T.query(l, r);
		c -= q;
		if (c < 0)
			c += MOD;
		c = int((c + (long long)q * ratio) % MOD);
	};

	cout << a << '\n';
	while (m--)
	{
		char c;
		int i, j, rji, rij;
		cin >> c;
		switch (c)
		{
		case 's':
			cin >> i >> j;
			i--;
			j--;
			rji = mdiv(A[j], A[i]);
			rij = mdiv(A[i], A[j]);
			set_val(i, rji, a, P);
			set_val(i, rji, b, Q);
			T.update(i, rji);
			set_val(j, rij, a, P);
			set_val(j, rij, b, Q);
			T.update(j, rij);
			swap(A[i], A[j]);
			break;
		case 'f':
			cin >> i;
			toggle(i, a, P);
			toggle(i, b, Q);
			break;
		case 'a':
			P.swap(Q);
			swap(a, b);
			break;
		}
		cout << a << '\n';
	}
}