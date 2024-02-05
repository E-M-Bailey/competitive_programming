#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<pair<int, int>> A(n);
	for (auto &[l, r] : A)
	{
		cin >> l >> r;
		l--;
		r--;
	}
	int ans = 0;
	for (int l = 0, r = 0; l < n;)
	{
		while (r < n && r <= A[l].second && A[r].first <= l)
			r++;
		if (l + 3 > r)
		{
			l++;
		}
		while (l + 3 <= r)
		{
			l += 3;
			ans++;
		}
	}
	cout << ans;
}
