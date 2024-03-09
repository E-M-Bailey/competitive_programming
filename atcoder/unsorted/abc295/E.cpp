#include <bits/stdc++.h>
using namespace std;

constexpr int64_t MOD = 998244353, PHI = MOD - 1;
int n, m, k, q = 0;

int64_t mpow(int64_t a, int64_t b)
{
	int64_t ans = 1;
	for (b = (b % PHI + PHI) % PHI; b; b /= 2, a = a * a % MOD)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

vector<int64_t> F, IF, I;
void pre(int n)
{
	F.resize(n + 1);
	IF.resize(n + 1);
	I.resize(n + 1);
	F[0] = IF[0] = 1;
	for (int i = 1; i <= n; i++)
		IF[i] = (F[i] = F[i - 1] * i % MOD) * (I[i] = mpow(i, -1)) % MOD;
}

int64_t nCr(int n, int r)
{
	if (r < 0 || r > n)
		return 0;
	return F[n] * IF[r] % MOD * IF[n - r] % MOD;
}

int64_t prob(int qq, int ct, int a)
{
	int64_t f = I[m];
	int64_t ans = nCr(qq, ct) * mpow(a * f % MOD, ct) % MOD * mpow((m - a) * f % MOD, qq - ct) % MOD;
	cerr << qq << ' ' << ct << ' ' << a << ' ' << ans << endl;
	return ans;
}

int main()
{
	cin >> n >> m >> k;
	k--;
	pre(max(n, m));
	vector<int> A;
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		if (a)
			A.push_back(a - 1);
		else
			q++;
	}
	sort(begin(A), end(A));
	vector<int> FR(m), PF(m + 1);
	for (int a : A)
		FR[a]++;
	for (int i = 0; i < m; i++)
		PF[i + 1] = PF[i] + FR[i];
	int64_t ans = 0;
	for (int i = 0; i < size(A); i++)
		ans += prob(q, k - i, A[i]) * A[i] % MOD;
	for (int i = 0; i < q; i++)
		for (int a = 0; a < m; a++)
			if (i + PF[a + 1] == k)
				ans += prob(q - 1, i, a + 1) * I[m] % MOD * a % MOD;
	cout << (ans + 1) % MOD;
}