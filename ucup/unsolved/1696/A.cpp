#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")

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
#define M	 (MAXN / 256)

int		a[MAXN];
int		r[MAXN];
__m256i g[MAXN][M + 1];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	int n, k;
	cin >> n >> k;
	rep(i, 0, n) cin >> a[i], r[--a[i]] = i;
	__m256i const bits[4]{_mm256_setr_epi64x(1, 0, 0, 0),
						  _mm256_setr_epi64x(0, 1, 0, 0),
						  _mm256_setr_epi64x(0, 0, 1, 0),
						  _mm256_setr_epi64x(0, 0, 0, 1)};
	for (int i = n - 2; i >= 0; i--)
	{
		int r1 = r[i], r2 = r[i + 1];
		for (int j = 0; j < M; j++)
			g[r1][j] = g[r2][j];
		int				   x = r2 / 256, y = (r2 % 256) / 64, z = r2 % 64;
		unsigned long long Z = 1ull << z;
		__m256i			   bit;
		switch (y)
		{
		case 0:
			bit = _mm256_setr_epi64x(Z, 0, 0, 0);
			break;
		case 1:
			bit = _mm256_setr_epi64x(0, Z, 0, 0);
			break;
		case 2:
			bit = _mm256_setr_epi64x(0, 0, Z, 0);
			break;
		case 3:
			bit = _mm256_setr_epi64x(0, 0, 0, Z);
			break;
		}
		g[r1][x] = _mm256_or_si256(g[r1][x], bit);
	}
	for (int i = 1; i < n; i++)
	{
		int x = i / 256;
		int A = i % 256, B = 256 - A;
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
	for (; (2 << p) <= k; p++)
	{
		for (int i = 0; i < n - (1 << p); i++)
			for (int j = 0; j < M; j++)
				g[i][j] &= g[i + (1 << p)][j];
	}
	int s = k - (1 << p);
	rep(i, 0, n - s) for (int j = 0; j < M; j++) g[i][j] &= g[i + s][j];
	ll ans = 0;
	rep(i, 0, n - k + 1) for (int j = 0; j < M; j++) ans += __builtin_popcountll(g[i][j]);
	cout << ans << '\n';
}