#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	string s;
	int	   ans = 0;
	while (cin >> s)
		for (char c : s)
			switch (c)
			{
			case '.':
				ans += 20;
				break;
			case 'O':
				ans += 10;
				break;
			case '\\':
			case '/':
				ans += 25;
				break;
			case 'A':
				ans += 35;
				break;
			case '^':
				ans += 5;
				break;
			case 'v':
				ans += 22;
				break;
			}
	cout << ans;
}
