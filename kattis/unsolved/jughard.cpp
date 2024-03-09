#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int a, b, d;
		cin >> a >> b >> d;
		int g = gcd(a, b);
		if (d % g == 0)
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}