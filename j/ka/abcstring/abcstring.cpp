#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	string s;
	cin >> s;

	int ans = 0;
	int e = 0, a = 0, b = 0, c = 0, ab = 0, ac = 0, bc = 0;
	for (char l : s)
	{
		int &x	= l == 'A' ? a : l == 'B' ? b : c;
		int &y	= l == 'A' ? b : l == 'B' ? c : a;
		int &z	= l == 'A' ? c : l == 'B' ? a : b;
		int &xy = l == 'A' ? ab : l == 'B' ? bc : ac;
		int &xz = l == 'A' ? ac : l == 'B' ? ab : bc;
		int &yz = l == 'A' ? bc : l == 'B' ? ac : ab;

		if (yz)
		{
			yz--;
			e++;
		}
		else if (y)
		{
			y--;
			xy++;
		}
		else if (z)
		{
			z--;
			xz++;
		}
		else if (e)
		{
			e--;
			x++;
		}
		else
		{
			ans++;
			x++;
		}
	}

	cout << ans;
}
