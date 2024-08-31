#include <bits/stdc++.h>

using namespace std;

int constexpr MOD = 1000000007, PHI = MOD - 1;

int mpow(int a, int b)
{
	int ans = 1;
	for (; b; a = int((long long)a * a % MOD), b /= 2)
		if (b % 2)
			ans = int((long long)ans * a % MOD);
	return ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	string s;
	int	   q;
	cin >> s >> q;

	int n = (int)size(s);

	vector<int> A(n);
	int			F[52]{};

	for (int i = 0; i < n; i++)
	{
		char c = s[i];
		A[i]   = c >= 'a' ? c - 'a' : c - 'A' + 26;
		F[A[i]]++;
	}

	vector<int> K0(n + 1), K1, K2;
	int			ANS[52][52];
	K0[0] = 1;
	for (int f : F)
		if (f)
			for (int i = n + 1; i-- > f;)
				if ((K0[i] += K0[i - f]) >= MOD)
					K0[i] -= MOD;

	for (int a = 0; a < 52; a++)
		if (F[a])
		{
			K1 = K0;
			for (int i = F[a]; i < n + 1; i++)
				if ((K1[i] -= K1[i - F[a]]) < 0)
					K1[i] += MOD;
			ANS[a][a] = K1[n / 2];

			for (int b = 0; b < a; b++)
				if (F[b])
				{
					K2 = K1;
					for (int i = F[b]; i < n + 1; i++)
						if ((K2[i] -= K2[i - F[b]]) < 0)
							K2[i] += MOD;
					ANS[a][b] = ANS[b][a] = K2[n / 2];
				}
		}

	vector<int> fac(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = int((long long)fac[i - 1] * i % MOD);

	int ans = 1;
	for (int f : F)
		ans = int((long long)ans * fac[f] % MOD);
	ans = int(2ll * fac[n / 2] * fac[n / 2] % MOD * mpow(ans, PHI - 1) % MOD);

	while (q--)
	{
		int x, y;
		cin >> x >> y;
		x--;
		y--;
		int a = A[x], b = A[y];
		cout << (long long)ans * ANS[a][b] % MOD << '\n';
	}
}
