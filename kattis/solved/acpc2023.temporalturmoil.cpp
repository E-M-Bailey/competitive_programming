#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		int i, j;
		cin >> i >> j;
		int t0 = 43200 + (43200 * i + 10) / 11;
		int k = j + (59 * t0) / 3600;
		int ans = j == 0 ? t0 : (k * 3600 + 58) / 59;
		ans %= 86400;
		int h = ans / 3600, m = ans % 3600 / 60, s = ans % 60;
		cout << h / 10 << h % 10 << ':' << m / 10 << m % 10 << ':' << s / 10 << s % 10 << '\n';
	}
}