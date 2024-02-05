#include <bits/stdc++.h>

using namespace std;

int64_t pow(int64_t a, int64_t b, int64_t m)
{
	int64_t p = 1;
	for (; b; b /= 2, a = a * a % m)
		if (b % 2)
			p = p * a % m;
	return p;
}

int64_t inv(int64_t a, int64_t p)
{
	return pow(a, p - 2, p);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--)
	{
		int64_t p;
		string	s;
		cin >> p >> s;
		int n = (int)size(s);

		vector<vector<int64_t>> A(n, vector<int64_t>(n + 1));
		for (int i = 0; i < n; i++)
		{
			A[i][0] = 1;
			for (int j = 1; j < n; j++)
				A[i][j] = A[i][j - 1] * (i + 1) % p;
			A[i][n] = s[i] == '*' ? 0 : s[i] - 'a' + 1;
		}

		for (int i = 0; i < n; i++)
		{
			int64_t ii = inv(A[i][i], p);
			for (int k = i; k < n + 1; k++)
				A[i][k] = A[i][k] * ii % p;
			for (int j = i + 1; j < n; j++)
			{
				int64_t mult = p - A[j][i];
				for (int k = i; k < n + 1; k++)
					A[j][k] = (A[j][k] + A[i][k] * mult) % p;
			}
		}

		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				int64_t mult = p - A[j][i];
				A[j][i]		 = 0;
				A[j][n]		 = (A[j][n] + A[i][n] * mult) % p;
			}
		}
		for (int i = 0; i < n; i++)
			cout << (A[i][n] + p) % p << ' ';
		cout << '\n';
	}
}
