#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<string> N{};
	auto rd = [&N, s = string{}, D = unordered_map<string, int>{}]() mutable
		{
			cin >> s;
			auto [it, ins] = D.try_emplace(move(s), (int)D.size());
			if (ins)
				N.push_back(it->first);
			return it->second;
		};
	int r;
	cin >> r;
	vector<tuple<int, int, int>> R(r);
	for (auto &[a, b, c] : R)
	{
		a = rd();
		b = rd();
		c = rd();
	}
	int m = (int)N.size();

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<vector<vector<double>>> DP(n, vector<vector<double>>(n, vector<double>(m, -numeric_limits<double>::infinity())));
		for (int i = 0; i < n; i++)
		{
			for (int j; (j = rd()) != m;)
			{
				double x;
				cin >> x;
				DP[i][i][j] = log(x);
			}
		}
		for (int l = 2; l <= n; l++)
			for (int i = 0, j = l; j <= n; i++, j++)
				for (int k = i + 1; k < j; k++)
					for (auto [a, b, c] : R)
						DP[i][j - 1][c] = max({
							DP[i][j - 1][c],
							DP[i][k - 1][a] + DP[k][j - 1][b],
							DP[i][k - 1][b] + DP[k][j - 1][a]
							});
		auto it = max_element(begin(DP[0][n - 1]), end(DP[0][n - 1]));

		if (finite(*it))
			cout << N[it - begin(DP[0][n - 1])] << '\n';
		else
			cout << "GAMEOVER\n";
	}

}