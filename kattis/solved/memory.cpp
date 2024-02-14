#include <bits/stdc++.h>

using namespace std;

int constexpr MOD = 1000000009;

int main()
{
	int	   a = 1, b = 0;
	string s;
	cin >> s;
	reverse(begin(s), end(s));
	for (char ch : s)
	{
		if (ch == '0')
		{
			if ((b += a) >= MOD)
				b -= MOD;
		}
		else
		{
			if ((a += b) >= MOD)
				a -= MOD;
		}
	}
	cout << a;
}
