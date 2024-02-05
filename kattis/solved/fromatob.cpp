#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int a, b;
	cin >> a >> b;
	int ans = 0;
	while (a > b)
	{
		ans++;
		if (a % 2)
			a++;
		else
			a /= 2;
	}
	ans += b - a;
	cout << ans;
}
