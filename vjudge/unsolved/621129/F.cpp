#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef __int128  lll;

lll const mod = 100000000003ll, phi = mod - 1;

lll mpow(lll a, lll b)
{
	if ((a %= mod) < 0)
		a += mod;
	if ((b %= phi) < 0)
		b += phi;
	lll ans = 1;
	for (; b; b /= 2, a = a * a % mod)
		if (b % 2)
			ans = ans * a % mod;
	return ans;
}

typedef vector<lll> poly;

poly operator*(poly const &A, poly const &B)
{
	if (A.empty() || B.empty())
		return {};
	poly C(size(A) + size(B) - 1);
	for (int i = 0; i < (int)size(A); i++)
		for (int j = 0; j < (int)size(B); j++)
			C[i + j] = (C[i + j] + A[i] * B[j]) % mod;
	return C;
}

poly operator*(poly const &A, lll b)
{
	return A * poly{b};
}
poly operator*(lll a, poly const &B)
{
	return poly{a} * B;
}

poly operator+(poly const &A, poly const &B)
{
	poly ans(max(size(A), size(B)));
	copy(begin(A), end(A), begin(ans));
	for (int i = 0; i < (int)size(B); i++)
		if ((ans[i] += B[i]) >= mod)
			ans[i] -= mod;
	return ans;
}
poly operator+(poly const &A, lll b)
{
	return A + poly{b};
}
poly operator+(lll a, poly const &B)
{
	return poly{a} + B;
}

poly operator-(poly const &A)
{
	poly ans(size(A));
	for (int i = 0; i < (int)size(A); i++)
		if (A[i])
			ans[i] = mod - A[i];
	return ans;
}
poly operator-(poly const &A, poly const &B)
{
	return A + -B;
}
poly operator-(poly const &A, lll b)
{
	return A - poly{b};
}
poly operator-(lll a, poly const &B)
{
	return poly{a} - B;
}

poly eval(poly const &A, poly const &B)
{
	poly ans;
	for (int i = (int)size(A); i-- > 0;)
		ans = ans * B + A[i];
	return ans;
}
lll eval(poly const &A, lll x)
{
	return A.empty() ? 0 : eval(A, poly{x})[0];
}

poly pref(poly const &A)
{
	static vector<poly> F{poly{1}};
	while (size(F) <= size(A))
	{
		int i = (int)size(F);
		F.emplace_back(i + 1);
		F[i][0] = 1;
		for (int j = 0; j < i; j++)
			F[i][0] -= (F[i][j + 1] = F[i - 1][j] * i % mod * mpow(j + 2, -1) % mod);
		if ((F[i][0] %= mod) < 0)
			F[i][0] += mod;
	}

	poly ans;
	for (int i = 0; i < (int)size(A); i++)
		ans = ans + A[i] * F[i];
	ans.insert(begin(ans), 0);

	return eval(ans, poly{mod - 1, 1});
}
lll sum(poly const &A, lll x1, lll x2)
{
	if (x1 >= x2)
		return 0;
	poly B	 = pref(A);
	lll	 ans = eval(B, x2) - eval(B, x1);
	if (ans < 0)
		ans += mod;
	return ans;
}

int main()
{
	ll r, c, k;
	cin >> r >> c >> k;
	lll R = r, C = c, K = k;
	if (R > C)
		swap(R, C);

	poly x{0, 1}, kx = K - x;

	// lll ans = (1 + 4 * sum(x, 0, K + 1)) % mod * R % mod * C % mod;
	lll ans = (R * C + 4 * sum(-x, 0, K + 1) + mod - 1) % mod * R % mod * C % mod;

	ans = (ans + 2 * R * sum(kx * kx, 0, min(C, K))) % mod;
	ans = (ans + 2 * C * sum(kx * kx, 0, min(R, K))) % mod;

	poly CC = -eval(pref(x), K - x);
	ans		= (ans + 4 * sum(CC * (x + 1), 0, min(K, R))) % mod;
	ans		= (ans + 4 * sum(CC * R, R, min(K, C))) % mod;
	ans		= (ans + 4 * sum(CC * (C + R - (x + 1)), C, min(K, C + R - 1))) % mod;

	cout << ll(ans * mpow(R * C, -2) % mod);
}
