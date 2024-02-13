#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	while (n--)
	{
		double b, p;
		cin >> b >> p;
		cout << fixed << setprecision(5) << (b - 1) * 60 / p << ' ' << b * 60 / p << ' ' << (b + 1) * 60 / p << '\n';
	}
}
