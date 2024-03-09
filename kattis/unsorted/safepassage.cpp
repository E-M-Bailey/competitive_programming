#include <bits/stdc++.h>

using namespace std;

int n;
int M;
vector<int> A;
vector<int> DP;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin >> n;
	M = (1 << n) - 1;
	A.resize(n);
	for (int& a : A)
		cin >> a;
	sort(A.begin(), A.end());

	DP.resize(1 << n);
	for (int a = 0; a < n; a++)
		for (int b = 0; b < a; b++)
			DP[(1 << a) | (1 << b)] = max(A[a], A[b]);
	for (int ct = 3; ct <= n; ct++)
	{
		for (int msk = 0; msk <= M; msk++)
		{
			if (__builtin_popcount(msk) != ct)
				continue;
			DP[msk] = INT_MAX;
			for (int a = 0; a < n; a++)
				if ((1 << a) & msk)
				{
					for (int b = 0; b < a; b++)
						if (1 << b & msk)
						{
							int c = __builtin_ctz((M ^ msk) ^ (1 << b) ^ (1 << a));
							DP[msk] = min(DP[msk], DP[msk ^ (1 << a) ^ (1 << b) ^ (1 << c)] + max(A[a], A[b]) + A[c]);
						}
				}
			/*
			int a = 31 - __builtin_clz(msk);
			for (int b = 0; b < a; b++)
				if ((1 << b) & msk)
				{
					int c = __builtin_ctz((M ^ msk) | (1 << b));
					cerr << a << ' ' << b << ' ' << c << ' ' << bitset<4>(msk) << '-' << bitset<4>(msk ^ (1 << a) ^ (1 << b) ^ (1 << c)) << endl;
					DP[msk] = min(DP[msk], DP[msk ^ (1 << a) ^ (1 << b) ^ (1 << c)] + max(A[a], A[b]) + A[c]);
				}
				*/
		}
	}

	cout << DP[M];
}