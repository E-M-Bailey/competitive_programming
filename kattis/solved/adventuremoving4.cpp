#include <bits/stdc++.h>

using namespace std;

int					   n = 0;
vector<vector<int>>	   DP;
vector<pair<int, int>> S;

int f(int i, int g)
{
	if (g < 0 || g > 200)
		return INT_MAX;
	auto &dp = DP[i][g];
	if (dp >= 0)
		return dp;
	dp = INT_MAX;

	int d = S[i].first - S[i - 1].first, p = S[i].second;
	for (int buy = max(0, g + d - 200); buy <= g; buy++)
	{
		if (p == INT_MAX && buy > 0)
			break;
		int rec = f(i - 1, g + d - buy);
		if (rec != INT_MAX)
			dp = min(dp, rec + buy * p);
	}

	return dp;
}

int main()
{
	int d, p, ds;
	cin >> ds;
	S.emplace_back(0, INT_MAX);
	DP.emplace_back(201, INT_MAX);
	DP[0][100] = 0;
	while (cin >> d >> p)
	{
		S.emplace_back(d, p);
		DP.emplace_back(201, -1);
	}
	S.emplace_back(ds, INT_MAX);
	DP.emplace_back(201, -1);

	int ans = INT_MAX;
	for (int g = 100; g <= 200; g++)
		ans = min(ans, f((int)S.size() - 1, g));

	if (ans == INT_MAX)
		cout << "Impossible";
	else
		cout << ans;
}
