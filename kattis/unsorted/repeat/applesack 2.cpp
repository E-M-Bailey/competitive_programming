#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	int ans = 1;
	while (n > 0)
	{
		n -= (n + k - 1) / k;
		ans++;
	}
	cout << ans;
}