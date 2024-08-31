#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int ans = INT_MIN;
	for (int i = 0; i < n; i++)
	{
		int cur = INT_MAX;
		for (int j = 0; j < n; j++)
		{
			int a;
			cin >> a;
			cur = min(cur, a);
		}
		ans = max(cur, ans);
	}
	cout << ans;
}

