#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k, d;
	cin >> n >> k >> d;
	int ans = 0;
	while (n--)
	{
		int di;
		cin >> di;
		ans += k + d - di >= 14;
	}
	cout << ans;
}
