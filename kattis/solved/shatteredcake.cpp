#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int w, n, a = 0;
	cin >> w >> n;
	while (n--)
	{
		int x, y;
		cin >> x >> y;
		a += x * y;
	}
	cout << a / w;
}
