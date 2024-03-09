#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<pair<int, int>> A(n);
	for (auto &[w, a] : A)
		cin >> w >> a;
	sort(begin(A), end(A));
	map<int, int> S = { make_pair(INT_MIN, m) };
	long long ans = 0;
	for (auto [w, a] : A)
	{
		int ct = 0;
		while (a > 0)
		{
			auto it = S.upper_bound(w - k);
			if (it == S.begin())
				break;
			--it;

			int amt = min(a, it->second);
			if ((it->second -= amt) == 0)
				S.erase(it);
			ct += amt;
			a -= amt;
		}
		ans += ct;
		S.emplace(w, ct);
	}
	cout << ans;
}