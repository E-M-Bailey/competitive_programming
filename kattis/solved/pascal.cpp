#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
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