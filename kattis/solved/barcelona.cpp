#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k;
	int ans = 0;
	int x	= INT_MAX;
	while (x != k)
	{
		cin >> x;
		ans++;
	}
	if (ans == 1)
		cout << "fyrst";
	else if (ans == 2)
		cout << "naestfyrst";
	else
		cout << ans << " fyrst";
}
