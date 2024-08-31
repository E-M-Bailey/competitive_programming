#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")

#include <bits/stdc++.h>

using namespace std;

template<int n>
void solve()
{
	constexpr int n1 = min(2500, n) + 1, n2 = min(2500, (n / 2) * ((n + 1) / 2)) + 1,
				  n3 = min(2500, (n / 3) * ((n + 1) / 3) * ((n + 2) / 3)) + 1;
	int    k;
	string s;
	cin >> k >> s;

	if (k >= n3)
	{
		cout << "-1";
		return;
	}

	array<array<array<bitset<n3>, n2>, n1>, n + 1> DP{};
	DP[0][0][0][0] = true;
	for (int i = 1; i <= n; i++)
	{
		char ch = s[i - 1];
		bool Q = ch == '?', X = ch != 'N' && ch != 'A' && ch != 'C', N = ch == 'N' || Q, A = ch == 'A' || Q,
			 C = ch == 'C' || Q;
		for (int a = i; a >= 0; a--)
			for (int b = (i / 2) * ((i + 1) / 2); b >= 0; b--)
			{
				if (X)
					DP[i][a][b] = DP[i - 1][a][b];
				if (C)
					DP[i][a][b] |= DP[i - 1][a][b] << b;
				if (A && b >= a)
					DP[i][a][b] |= DP[i - 1][a][b - a];
				if (N && a >= 1)
					DP[i][a][b] |= DP[i - 1][a - 1][b];
			}
	}

	int a = -1, b = -1, c = k, i = n;
	for (int aa = 0; a < 0 && aa < n1; aa++)
		for (int bb = 0; bb < n2; bb++)
			if (DP[i][aa][bb][k])
			{
				a = aa;
				b = bb;
				break;
			}
	if (a < 0)
	{
		cout << "-1";
		return;
	}

	while (i--)
	{
		char &ch = s[i];
		bool  Q = ch == '?', X = ch != 'N' && ch != 'A' && ch != 'C', A = ch == 'A' || Q, C = ch == 'C' || Q;
		if (X && DP[i][a][b][c])
		{
			if (Q)
				ch = 'X';
		}
		else if (C && c >= b && DP[i][a][b][c - b])
		{
			c -= b;
			if (Q)
				ch = 'C';
		}
		else if (A && b >= a && DP[i][a][b - a][c])
		{
			b -= a;
			if (Q)
				ch = 'A';
		}
		else
		{
			a--;
			if (Q)
				ch = 'N';
		}
	}
	cout << s;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	switch (n)
	{
#define C(a)                                                                                                           \
	case a:                                                                                                            \
		solve<a>();                                                                                                    \
		break;
#define D(a) C(a + 1) C(a + 2) C(a + 3) C(a + 4) C(a + 5) C(a + 6) C(a + 7) C(a + 8) C(a + 9) C(a + 10)
		D(0) D(10) D(20) D(30)
#undef D
#undef C
	}
}
