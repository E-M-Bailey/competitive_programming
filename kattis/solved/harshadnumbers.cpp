#include <bits/stdc++.h>

using namespace std;

int ds(int x)
{
	int ans = 0;
	while (x)
	{
		ans += x % 10;
		x /= 10;
	}
	return ans;
}

int main()
{
	int n;
	cin >> n;
	while (n % ds(n))
		n++;
	cout << n;
}
