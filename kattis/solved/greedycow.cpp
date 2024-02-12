#include <bits/stdc++.h>

using namespace std;

constexpr __int128 C(int64_t n, int r)
{
	if (r < 0 || r > n)
		return 0;
	if (r > n - r)
		r = int(n - r);
	__int128 nCr = 1;
	for (int i = 0; i < r; i++)
		if ((nCr = nCr * (n - i) / (i + 1)) >= INT64_MAX)
			return INT64_MAX;
	return (int64_t)nCr;
}

template<int... c>
constexpr array<int, max({c...}) + 1> freq()
{
	array<int, max({c...}) + 1> F{};
	(++F[c], ...);
	return F;
}

template<int... c>
__int128 helper(int64_t x, int64_t y, int64_t f, int64_t g)
{
	constexpr int			n = max({c...}) + 1;
	constexpr array<int, n> F = freq<c...>();

	__int128 ans = 0;
	for (int i = 0; i <= n; i++)
	{
		unsigned __int128 term = C(x, i) * C(y, n - i);

		bool z = term == 0, m = term >= INT64_MAX;

		for (int j = 0; !z && j < i; j++)
		{
			auto cur = C(f, F[j]);
			z |= cur == 0;
			m |= (term *= cur) >= INT64_MAX;
		}
		for (int j = i; !z && j < n; j++)
		{
			auto cur = C(g, F[j]);
			z |= cur == 0;
			m |= (term *= cur) >= INT64_MAX;
		}
		if (!z)
		{
			if (m)
				return INT64_MAX;
			ans += (__int128)term;
		}
	}
	return min((__int128)INT64_MAX, ans);
}

int64_t pastures(int64_t n, int64_t m)
{
	int64_t	 f = m / n, g = f + 1, y = m % n, x = n - y;
	__int128 ans = 1 + helper<0, 1>(x, y, f, g) + helper<0, 1, 2, 3>(x, y, f, g) + helper<0, 1, 2, 2>(x, y, f, g) + helper<0, 1, 1, 2>(x, y, f, g) +
				   helper<0, 0, 1, 2>(x, y, f, g) + helper<0, 0, 1, 1>(x, y, f, g);
	return (int64_t)min((__int128)INT64_MAX, ans);
}

bool parallel(pair<int, int> a, pair<int, int> b, pair<int, int> c)
{
	int64_t dx1 = b.first - a.first, dx2 = c.first - b.first;
	int64_t dy1 = b.second - a.second, dy2 = c.second - b.second;
	return dx1 * dy2 == dx2 * dy1;
}

int main()
{
	int64_t k;
	int		n;
	cin >> k >> n;

	deque<pair<int, int>> P;
	while (n--)
	{
		int x, y;
		cin >> x >> y;
		if (!P.empty() && P.back() == pair{x, y})
			continue;
		if (size(P) >= 2 && parallel(P[size(P) - 2], P.back(), {x, y}))
			P.pop_back();
		P.emplace_back(x, y);
	}
	while (size(P) >= 2)
	{
		if (P.back() == P.front() || (size(P) >= 3 && parallel(P[size(P) - 2], P.back(), P.front())))
			P.pop_back();
		else if (size(P) >= 3 && parallel(P.back(), P.front(), P[1]))
			P.pop_front();
		else
			break;
	}
	n = (int)size(P);

	int64_t lo = 0, hi = k;
	while (lo < hi)
	{
		int64_t m = (lo + hi) / 2;
		if (pastures(n, m) >= k)
			hi = m;
		else
			lo = m + 1;
	}
	cout << lo;
}
