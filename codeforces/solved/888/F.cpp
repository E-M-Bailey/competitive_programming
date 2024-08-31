#include <bits/stdc++.h>

using namespace std;

long long constexpr MOD = 1000000007;

int A[500][500], F[500][500], G[500][500];

int g(int l, int r);

int f(int l, int r)
{
	int &dp = F[l][r];
	if (dp < 0)
	{
		dp = 0;
		for (int i = l + 1; i <= r; i++)
			if (A[l][i])
				dp = int((dp + (long long)g(l, i) * f(i, r)) % MOD);
	}
	return dp;
}

int g(int l, int r)
{
	int &dp = G[l][r];
	if (dp < 0)
	{
		dp = f(l + 1, r);
		for (int i = l + 1; i < r; i++)
			if (A[l][i])
				dp = int((dp + (long long)g(l, i) * g(i, r)) % MOD);
	}
	return dp;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> A[i][j];
			F[i][j] = G[i][j] = -1;
		}
		F[i][i] = 1;
	}

	cout << f(0, n - 1);
}
