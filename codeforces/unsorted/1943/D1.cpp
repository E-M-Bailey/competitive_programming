#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	while (t--)
		go();
}

// DP(n, a, b):
// c >= b - a
// a >= b - c
// DP(n + 1, b, c) = sum[a >= b - c] DP(n + 1, a, b)

void go()
{
	int64_t n, k, p;
	cin >> n >> k >> p;
	k++;
	vector<vector<vector<int64_t>>> DP(n + 2, vector<vector<int64_t>>(k, vector<int64_t>(k)));
	vector<int64_t>					P(k + 1);
	DP[0][0][0] = 1;
	for (int i = 0; i <= n; i++)
	{
		for (int b = 0; b < k; b++)
		{
			for (int a = 0; a < k; a++)
				P[a + 1] = (P[a] + DP[i][a][b]) % p;
			for (int c = 0; c < k; c++)
			{
				DP[i + 1][b][c] = ((P.back() - P[max(0, b - c)]) % p + p) % p;
				//cerr << i + 1 << ' ' << b << ' ' << c << ' ' << DP[i + 1][b][c] << endl;
			}
		}
	}

	int64_t ans = 0;
	for (int a = 0; a < k; a++)
		for (int b = 0; b < k; b++)
		{
			if (b == 0)
				ans = (ans + DP.back()[a][b]) % p;
		}
	cout << ans << '\n';
}
