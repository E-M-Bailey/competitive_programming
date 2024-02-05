#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int c, n;
	cin >> c >> n;
	int	 a		  = 0;
	bool possible = true;
	for (int i = 0; possible && i < n; i++)
	{
		int l, e, s;
		cin >> l >> e >> s;
		a -= l;
		possible &= a >= 0;
		a += e;
		if (s > 0)
			possible &= a == c;
		else
			possible &= a <= c;
	}
	possible &= a == 0;
	cout << (possible ? "possible" : "impossible");
}
