#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int N, M, a, b, c, d, e, f, v0;
	cin >> N >> M >> a >> b >> c >> d >> e >> f >> v0;

	vector<int> V{ v0 }, L{ 0 };
	vector<vector<int>> DP{ vector<int>(N + 1, numeric_limits<int>::min()) };
	DP[0][0] = 0;
	int best = 0;

	for (int i = 1; i <= M; i++)
	{
		assert(i == size(V));
		assert(i == size(L));
		for (int j = 0; j < i; j++)
		{
			assert(j < size(L));
			L[j] = (d * i + e * V[j]) % f;
			V[j] = (a * i + b * V[j]) % c + 1;
		}
		L.push_back(0);
		V.push_back(0);
		DP.emplace_back(N + 1, numeric_limits<int>::min());

		for (int j = 0; j <= N; j++)
			for (int k = 0; k <= i; k++)
			{
				int v = V[k], l = L[k];
				assert(i < size(DP));
				assert(j < size(DP[i]));
				if (j - v >= 0)
				{
					assert(k < size(DP));
					assert(j - v < size(DP[k]));
					best = max(best, DP[i][j] = max(DP[i][j], DP[k][j - v] + l));
				}
			}
	}
	cout << best;
}
