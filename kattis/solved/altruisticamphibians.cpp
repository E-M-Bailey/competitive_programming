#include <bits/stdc++.h>

using namespace std;

int DP[200'000'002];

int main()
{
	int n, d;
	cin >> n >> d;
	vector<tuple<int, int, int>> A(n);
	for (auto &[w, h, l] : A)
		cin >> l >> w >> h;
	sort(rbegin(A), rend(A));

	int ans = 0;
	for (auto [w, h, l] : A)
	{
		for (int i = 0; i < w; i++)
			DP[i] = max(DP[i], min(100'000'000, DP[i + w] + h));
		ans += DP[w] + l > d;
	}
	cout << ans;
}