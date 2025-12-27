#include <bits/stdc++.h>

using namespace std;

int t, m, n, N, k, P[2000], R[2000];
tuple<int, int, int> E[1999000];

int find(int x)
{
	while (x != P[x])
		tie(x, P[x]) = pair(P[x], P[P[x]]);
	return x;
}

bool onion(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y)
		return false;
	if (R[x] < R[y])
		swap(x, y);
	P[y] = x;
	R[x] += R[x] == R[y];
	return true;
}

int main()
{
	cin >> t;
	while (t--)
	{
		cin >> m >> n;
		N = n * (n - 1) / 2;
		for (k = 0; k < N; ++k)
		{
			auto &[d, i, j] = E[k];
			cin >> i >> j >> d;
		}
		sort(E, E + N);
		fill(P, P + n, 0);
		iota(P, P + n, 0);

		for (k = 0; k < N; ++k)
		{
			auto [d, i, j] = E[k];
			if (onion(i, j))
				m -= d;
		}
		cout << (m >= n ? "yes\n" : "no\n");
	}
}