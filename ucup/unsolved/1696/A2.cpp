#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma")

#include <bits/stdc++.h>
#include <immintrin.h>
#include <nmmintrin.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x)		 begin(x), end(x)
#define sz(x)		 (int)(x).size()
#define F			 first
#define S			 second
#define pb			 push_back
typedef long long	   ll;
typedef pair<int, int> pii;
typedef vector<int>	   vi;

#define MAXN 50176
#define M	 (MAXN / 64)

// int				   a[MAXN];
alignas(256) unsigned short r[MAXN];
alignas(256) unsigned long long g[MAXN][M + 1];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	int n, k, a;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
	{
		cin >> a;
		r[a - 1] = (unsigned short)i;
	}
	for (int i = n - 2; i >= 0; i--)
	{
		for (int j = 0; j < M; j++)
			g[r[i]][j] = g[r[i + 1]][j];
		g[r[i]][r[i + 1] / 64] |= 1ull << (r[i + 1] % 64);
	}
#pragma GCC unroll 64
	for (int i = 1; i < n; i++)
	{
		int x = i / 64;
		int A = i % 64, B = 64 - A;
		if (A)
		{
			for (int j = x; j < M; j++)
				g[i][j - x] = (g[i][j] >> A) | (g[i][j + 1] << B);
		}
		else
			for (int j = x; j < M; j++)
				g[i][j - x] = g[i][j];
	}
	int p = 0;
	for (; (2 << p) < k; p++)
		for (int i = 0; i < n - (1 << p); i++)
			for (int j = 0; j < M - i / 64; j++)
				g[i][j] &= g[i + (1 << p)][j];
	int s	= k - (1 << p);
	int ans = 0;
	for (int i = 0; i < n - k + 1; i++)
		for (int j = 0; j < M - i / 64; j++)
			ans += __builtin_popcountll(g[i][j] & g[i + s][j]);
	cout << ans << '\n';
}
