#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int r, c, d, n;
	cin >> r >> c >> d >> n;
	vector<int> C(d + 1);
	for (int i = 0; i <= d; i++)
		while (C[i] * C[i] + i * i <= d * d)
			C[i]++;

	unordered_map<int, vector<pair<int, int>>> D;
	for (int idx = 0; idx < n; idx++)
	{
		int i, j;
		cin >> i >> j;
		for (int k = -d; k <= d; k++)
			if (1 <= k + i && k + i <= r)
			{
				int dist = C[abs(k)];
				D[k + i].emplace_back(max(j - dist + 1, 1), 1);
				D[k + i].emplace_back(min(j + dist, c + 1), -1);
			}
		D[i].emplace_back(j, n);
		D[i].emplace_back(j + 1, -n);
	}

	int ans = (int)size(D) < r ? 0 : n;
	for (auto &[y, row] : D)
	{
		row.emplace_back(1, 0);
		row.emplace_back(c, 0);
		row.emplace_back(c + 1, 0);
		sort(begin(row), end(row));

		int cnt = 0, t, pos = 0;
		while ((t = row[pos].first) <= c)
		{
			do
				cnt += row[pos++].second;
			while (row[pos].first == t);
			ans = min(ans, cnt);
		}
	}
	cout << ans;
}
