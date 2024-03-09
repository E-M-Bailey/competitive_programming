#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

/*
ull modmul(ull a, ull b, ull m)
{
	ll ret = a * b - m * ull(1.L / m * a * b);
	return ret + m * (ret < 0) - m * (ret >= (ll)m);
}

ull modpow(ull b, ull e, ull m)
{
	ull ans = 1;
	for (; e; b = modmul(b, b, m), e /= 2)
		if (e % 2) ans = modmul(ans, b, m);
	return ans;
}

bool is_prime(ull n)
{
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[]{ 2, 325, 9375, 28178, 450775, 9780504, 1795265022 };
	ull s = __builtin_ctzll(n - 1), d = n >> s;
	for (ull a : A)
	{
		ull p = modpow(a % n, d, n), i = s;
		while (p != 1 && p != n - 2 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n - 1 && i != s)
			return 0;
	}
	return 1;
}

ull pollard(ull n)
{
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1)
	{
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n)
{
	if (n <= 1)
		return {};
	if (is_prime(n))
		return { n };
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), begin(r), end(r));
	return l;
}
*/

ull P[]{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };

int main()
{
	ull n;
	cin >> n;

	ull den = 1;
	int m = 0;
	while (m < 15 && den * P[m] <= n)
		den *= P[m++];

	ull phi = den;
	while (m-- > 0)
		phi = phi / P[m] * (P[m] - 1);

	ull num = den - phi;
	ull g = __gcd(den, num);
	num /= g;
	den /= g;
	cout << num << '/' << den;
}