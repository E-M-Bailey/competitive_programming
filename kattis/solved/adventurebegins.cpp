#include <bits/stdc++.h>

using namespace std;

int constexpr MOD = 1000000007;

template<typename T, typename F>
struct ft
{
	vector<T> s;
	F const	  f;

	ft(int n, F const &op = F{}) : s(n), f(op) {}
	T query(int i)
	{
		if (i == 0)
			return {};
		T ans = s[i - 1];
		while (i &= i - 1)
			ans = f(ans, s[i - 1]);
		return ans;
	}
	void update(int i, T del)
	{
		for (; i < (int)size(s); i |= i + 1)
			s[i] = f(s[i], del);
	}
};

struct rurq
{
	typedef int T;

	static constexpr T add(T x, T y) noexcept
	{
		auto ans = x + y;
		return ans >= MOD ? ans - MOD : ans;
	}
	static constexpr T mult(T x, int y) noexcept
	{
		return int((long long)x * y % MOD);
	}
	static constexpr T neg(T x) noexcept
	{
		return x ? MOD - x : 0;
	}
	struct adder
	{
		constexpr pair<T, T> operator()(pair<T, T> const &x, pair<T, T> const &y) const noexcept
		{
			return {add(x.first, y.first), add(x.second, y.second)};
		}
	};

	ft<pair<T, T>, adder> s;
	rurq(int n) : s(n, adder{}) {}
	T query(int i)
	{
		auto ans = s.query(i);
		return add(ans.first, mult(ans.second, i));
	}
	void update(int i, T del)
	{
		s.update(0, {0, del});
		if (i < (int)s.s.size())
			s.update(i, {mult(del, i), neg(del)});
	}
};

int minv(int a)
{
	int x = 0, u = MOD, y = 1, v = a;
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
	return x;
}


int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, q;
	cin >> n >> q;

	rurq	  E(n);
	long long sum = 0;

	while (q--)
	{
		char c;
		cin >> c;
		if (c == '1')
		{
			int u, v;
			cin >> u >> v;
			u--;

			long long p = minv(v - u);

			sum = (sum + 2 * ((long long)E.query(v) + MOD - E.query(u)) * p + 1) % MOD;
			E.update(v, (int)p);
			E.update(u, MOD - (int)p);
		}
		else
		{
			cout << sum << '\n';
		}
	}
}