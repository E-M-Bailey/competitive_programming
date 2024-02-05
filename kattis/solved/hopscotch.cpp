#include <bits/stdc++.h>

using namespace std;

constexpr int64_t MOD = 1e9 + 7;
constexpr int	  LIM = 2e6;

int64_t mpow(int64_t a, int b)
{
	int64_t ans = 1;
	for (; b; b /= 2, a = a * a % MOD)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

int64_t minv(int64_t a)
{
	return mpow(a, MOD - 2);
}

int64_t F[LIM], IF[LIM];

int64_t nCr(int n, int r)
{
	return r < 0 || r > n ? 0 : F[n] * IF[r] % MOD * IF[n - r] % MOD;
}

int main()
{
	F[0] = IF[0] = 1;
	for (int i = 1; i < LIM; i++)
		IF[i] = minv(F[i] = F[i - 1] * i % MOD);

	int N, X, Y;
	cin >> N >> X >> Y;
	if (X < Y)
		swap(X, Y);

	int64_t ans = 0;
	for (int k = 1; k * X <= N; k++)
		ans += nCr(N - k * X + k - 1, k - 1) * nCr(N - k * Y + k - 1, k - 1) % MOD;

	cout << ans % MOD;
}
