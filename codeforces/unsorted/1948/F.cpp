#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin.tie(0)->sync_with_stdio(0);
	int t = 1;
	//cin >> t;
	while (t--)
	{
		go();
	}
}

int64_t constexpr MOD = 998244353;
int64_t constexpr PHI = MOD - 1;

int64_t mpow(int64_t x, int64_t y)
{
	y %= PHI;
	if (y < 0)
		y += PHI;
	int64_t ans = 1;
	for (; y; y /= 2, x = x * x % MOD)
		if (y % 2)
			ans = ans * x % MOD;
	return ans;
}

int64_t fac(int n)
{
	static vector<int64_t> F{1};
	while ((int)size(F) <= n)
		F.push_back((F.back() * size(F)) % MOD);
	return F[n];
}

int64_t binom(int n, int r)
{
	if (r < 0 || r > n)
		return 0;
	return fac(n) * mpow(fac(r) * fac(n - r) % MOD, -1) % MOD;
}

void go()
{
	int n, q;
	cin >> n >> q;
	vector<int64_t> A(n), B(n);
	for (auto &a : A)
		cin >> a;
	for (auto &b : B)
		cin >> b;

	vector<int> PA(n + 1), PB(n + 1);
	partial_sum(begin(A), end(A), begin(PA) + 1);
	partial_sum(begin(B), end(B), begin(PB) + 1);
	int AA = PA.back(), BB = PB.back();

	int64_t			p2 = mpow(2, -BB);
	vector<int64_t> ans(BB + 2);
	for (int i = 0; i <= BB; i++)
		ans[i + 1] = (ans[i] + p2 * binom(BB, i)) % MOD;

	while (q--)
	{
		int l, r;
		cin >> l >> r;
		l--;
		int a = PA[r] - PA[l], b = PB[r] - PB[l];
		cout << ans[max(0, min(BB + 1, 2 * a + b - AA))] << ' ';
	}
}
