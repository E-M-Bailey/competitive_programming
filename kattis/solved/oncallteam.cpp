#include <bits/stdc++.h>

using namespace std;

void sos(vector<int> &A)
{
	for (int bit = 1; bit < (int)size(A); bit <<= 1)
		for (int j = (int)size(A); j-- > 0;)
			if (j & bit)
				A[j] += A[j ^ bit];
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m, M;
	cin >> n >> m;
	M = 1 << m;

	vector<int> F(M);

	for (int i = 0; i < n; i++)
	{
		int a = 0;
		for (int j = 0; j < m; j++)
		{
			char c;
			cin >> c;
			a = a * 2 + c - '0';
		}
		F[a]++;
	}

	sos(F);

	int ans = m;
	for (int mask = 0; mask < M; mask++)
	{
		int lsize = n - F[(M - 1) ^ mask], rsize = __builtin_popcount(mask);
		if (lsize < rsize)
			ans = min(ans, rsize - 1);
	}
	cout << ans;
}
