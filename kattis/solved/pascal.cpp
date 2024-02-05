#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	int ans = n;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
		{
			ans = i;
			break;
		}
	ans = n - n / ans;
	cout << ans;
}
