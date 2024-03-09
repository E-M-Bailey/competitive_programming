#include <bits/stdc++.h>

using namespace std;

int constexpr CS = 5, MAXN = 3 * CS;

int64_t D[17][17];
int64_t C[1 << MAXN];

int main()
{
	int n, m;
	cin >> n >> m;

	for (int i = 0; i <= n + 1; i++)
		for (int j = 0; j <= n + 1; j++)
			D[i][j] = i == j ? 0 : INT_MAX;

	while (m--)
	{
		int64_t u, v, d;
		cin >> u >> v >> d;
		D[u][v] = D[v][u] = min(D[v][u], d);
	}

	for (int k = 0; k <= n + 1; k++)
		for (int i = 0; i <= n + 1; i++)
			for (int j = 0; j <= n + 1; j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

	vector<int> P{ 0 };
	for (int mask = 0; mask < (1 << n); mask++)
	{
		C[mask] = INT_MAX;
		if (__builtin_popcount(mask) > CS)
			continue;
		P.resize(1);
		for (int m2 = mask; m2; m2 &= m2 - 1)
			P.push_back(__builtin_ctz(m2) + 1);
		P.push_back(n + 1);

		// for (int p : P)
		// 	cerr << p << ' ';
		// cerr << bitset<6>(mask) << endl;

		do
		{
			int64_t c = 5 * __builtin_popcount(mask);
			for (int i = 1; i < (int)P.size(); i++)
				c += D[P[i - 1]][P[i]];
			C[mask] = min(C[mask], c);
		} while (next_permutation(begin(P) + 1, end(P) - 1));
	}


	// for (int i = 0; i <= n + 1; i++)
	// {
	// 	for (int j = 0; j <= n + 1; j++)
	// 		cerr << D[i][j] << ' ';
	// 	cerr << endl;
	// }

	int M = (1 << n) - 1;
	int64_t ans = INT_MAX;
	if (n <= CS)
		ans = C[M];
	else if (n <= 2 * CS)
	{
		for (int a = 1; a <= M; a++)
		{
			int pa = __builtin_popcount(a);
			if (pa > CS || n - pa > CS)
				continue;
			int b = M ^ a;
			//cerr << bitset<6>(a) << ' ' << C[a] << ' ' << C[b] << endl;
			ans = min(ans, max(C[a], C[b]));
		}
	}
	else
	{
		for (int a = 1; a <= M; a++)
		{
			int pa = __builtin_popcount(a);
			if (pa > CS || n - pa > 10)
				continue;
			int bc = M ^ a;
			for (int b = bc; b; b = (b - 1) & bc)
			{
				int pb = __builtin_popcount(b);
				if (pb > CS || n - pa - pb > CS)
					continue;
				int c = bc ^ b;
				//cerr << bitset<6>(a) << ' ' << C[a] << ' ' << bitset<6>(b) << ' ' << C[b] << ' ' << bitset<6>(c) << ' ' << C[c] << endl;
				ans = min(ans, max({ C[a], C[b], C[c] }));
			}
		}
	}
	cout << ans;
}