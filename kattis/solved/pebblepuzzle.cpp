#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	array<__uint128_t, 100> A, B, C;
	string					s;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		fill(begin(A), begin(A) + m, 0);
		fill(begin(B), begin(B) + m, 0);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (cin >> s, s[0] == 'B')
					A[j] |= (__uint128_t)1 << i;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (cin >> s, s[0] == 'B')
					B[j] |= (__uint128_t)1 << i;
		sort(begin(B), begin(B) + m);
		bool ans = false;
		for (int i = 0; !ans && i < m; i++)
		{
			__uint128_t mask = A[i] ^ B[0];
			for (int j = 0; j < m; j++)
				C[j] = A[j] ^ mask;
			sort(begin(C), begin(C) + m);
			ans = equal(begin(B), begin(B) + m, begin(C));
		}
		cout << (ans ? "YES\n" : "NO\n");
	}
}
