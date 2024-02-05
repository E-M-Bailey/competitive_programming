#include <bits/stdc++.h>

using namespace std;

// Source: KACTL
uint64_t modmul(uint64_t a, uint64_t b, uint64_t M)
{
	long long ret = a * b - M * uint64_t(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (long long)M);
}
uint64_t modpow(uint64_t b, uint64_t e, uint64_t mod)
{
	uint64_t ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1)
			ans = modmul(ans, b, mod);
	return ans;
}
bool isPrime(uint64_t n)
{
	if (n < 2 || n % 6 % 4 != 1)
		return (n | 1) == 3;
	uint64_t A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n - 1), d = n >> s;
	for (uint64_t a : A)
	{
		uint64_t p = modpow(a % n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n - 1 && i != s)
			return 0;
	}
	return 1;
}
uint64_t pollard(uint64_t n)
{
	auto f = [n](uint64_t x)
	{
		return modmul(x, x, n) + 1;
	};
	uint64_t x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1)
	{
		if (x == y)
			x = ++i, y = f(x);
		if ((q = modmul(prd, max(x, y) - min(x, y), n)))
			prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<uint64_t> factor(uint64_t n)
{
	if (n == 1)
		return {};
	if (isPrime(n))
		return {n};
	uint64_t x = pollard(n);
	auto	 l = factor(x), r = factor(n / x);
	l.insert(end(l), begin(r), end(r));
	return l;
}
vector<uint64_t> input()
{
	uint64_t n;
	cin >> n;
	return factor(n);
}

uint64_t constexpr MOD = 1e9 + 7;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	uint64_t P;
	int		n, m;
	cin >> P >> n >> m;

	unordered_map<uint64_t, int> F;
	while (n--)
		for (auto p : input())
			F[p]--;
	while (m--)
		for (auto p : input())
			F[p]++;

	uint64_t ans = 1;
	for (auto [p, f] : F)
	{
		if (f < 0)
		{
			ans = 0;
			break;
		}
		else if (f >= 1)
		{
			uint64_t cur = (modpow(f + 1, P, MOD) + 2 * (MOD - modpow(f, P, MOD)) + modpow(f - 1, P, MOD)) % MOD;
			ans = modmul(ans, cur, MOD);
		}
	}
	cout << ans;
}
