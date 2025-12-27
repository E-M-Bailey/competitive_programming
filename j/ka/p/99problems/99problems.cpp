#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int ans = n;
	while (ans % 100 != 99)
		ans++;
	if (ans - n > 50 && ans > 100)
		ans -= 100;
	cout << ans;
}
