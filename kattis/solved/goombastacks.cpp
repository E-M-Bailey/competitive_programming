#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	int sum = 0;
	while (n--)
	{
		int g, b;
		cin >> g >> b;
		if ((sum += g) < b)
		{
			cout << "impossible";
			return 0;
		}
	}
	cout << "possible";
}
