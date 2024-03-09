#include <bits/stdc++.h>

using namespace std;

int n, k, l;
vector<bool> A;

int64_t solve()
{
	int64_t lo = 0, hi = n;
	vector<pair<int64_t, int>> DP(n + 1);
	int64_t ans = INT64_MAX;
	while (lo < hi)
	{
		int64_t lam = (hi + lo) / 2;
		DP[0].first = 0;
		DP[0].second = 0;
		for (int i = 1; i <= n; i++)
		{
			DP[i] = DP[i - 1];
			DP[i].first += A[i - 1];
			pair<int64_t, int> pr = i < l ? pair<int64_t, int>(0, 0) : DP[i - l];
			pr.first += lam;
			pr.second += 1;
			DP[i] = min(DP[i], pr);
		}
		//cerr << lam << ' ' << DP[n].first << ' ' << DP[n].second << ' ' << DP[n].first - (int64_t)DP[n].second * lam << endl;
		if (DP[n].second > k)
			lo = lam + 1;
		else
		{
			hi = lam;
			ans = DP[n].first - (int64_t)k * lam;
		}
	}
	return ans;
}

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin >> n >> k >> l;
	k = min(k, (l + n - 1) / l);
	A.resize(n);
	for (int i = 0; i < n; i++)
	{
		char a;
		cin >> a;
		A[i] = a <= 'Z';
	}

	auto ans = solve();
	for (int i = 0; i < n; i++)
		A[i] = !A[i];
	ans = min(ans, solve());
	cout << ans;
}