#include <bits/stdc++.h>

using namespace std;

long long constexpr MOD = 998244353, PHI = MOD - 1;

int h;

long long mpow(long long a, long long b)
{
	if ((a %= MOD) < 0)
		a += MOD;
	if ((b %= PHI) < 0)
		b += PHI;
	long long ans = 1;
	for (; b; a = a * a % MOD, b /= 2)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

vector<long long> conv(vector<long long> const &A, vector<long long> const &B)
{
	vector<long long> ans(h + 1);
	for (int i = 0; i <= h; i++)
		for (int j = 0; j <= h; j++)
			ans[min(i + j, h)] = (ans[min(i + j, h)] + A[i] * B[j]) % MOD;
	return ans;
}

vector<long long> cpow(vector<long long> A, long long b)
{
	vector<long long> ans(h + 1);
	ans[0] = 1;
	for (; b; A = conv(A, A), b /= 2)
		if (b % 2)
			ans = conv(ans, A);
	return ans;
}

int main()
{
	long long n;
	int		  m;
	cin >> h >> n >> m;

	vector<long long> A(h + 1);
	for (int i = 0; i < m; i++)
	{
		int r;
		cin >> r;
		A[min(r, h)]++;
	}

	cout << cpow(A, n).back() * mpow(m, -n) % MOD;
}
