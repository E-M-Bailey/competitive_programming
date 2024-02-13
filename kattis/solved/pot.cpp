#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, ans = 0;
	cin >> n;
	while (n--)
	{
		int a, cur = 1;
		cin >> a;
		for (int i = 0; i < a % 10; i++)
			cur *= a / 10;
		ans += cur;
	}
	cout << ans;
}
