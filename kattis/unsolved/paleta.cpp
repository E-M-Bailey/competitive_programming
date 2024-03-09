#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1000000007;

int n, k;

int64_t cyc(int l)
{
	static vector<pair<int64_t, int64_t>> DP{ pair{0, 0}, pair{k, 0} };
	if (l == 1)
		return k;
	if (k == 1)
		return 0;
	if (k == 2)
		return l % 2 == 0 ? 2 : 0;

	while ((int)DP.size() <= l)
	{
		DP.emplace_back(DP.back().second, (DP.back().second * (k - 2) + DP.back().first * (k - 1)) % MOD);
	}
	return DP[l].second;
}

int main()
{
	cin >> n >> k;

	vector<int> F(n);
	for (int i = 0; i < n; i++)
	{
		cin >> F[i];
		F[i]--;
	}

	vector<bool> vis(n), ons(n);
	vector<int> s;

	int64_t ans = 1;
	int rem = n;

	for (int i = 0; i < n; i++)
	{
		if (vis[i])
			continue;
		s.clear();
		int j = i;
		for (; !vis[j]; j = F[j])
		{
			s.push_back(j);
			ons[j] = true;
			vis[j] = true;
		}
		bool done = !ons[j];
		for (int x : s)
			ons[x] = false;
		if (done)
			continue;
		int len = 1;
		while (s.back() != j)
		{
			len++;
			s.pop_back();
		}
		rem -= len;
		ans = ans * cyc(len) % MOD;
	}
	while (rem--)
		ans = ans * (k - 1) % MOD;
	cout << ans << '\n';
}