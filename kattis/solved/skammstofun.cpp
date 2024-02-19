#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	while (n--)
	{
		string s;
		cin >> s;
		if (s[0] <= 'Z')
			cout << s[0];
	}
}
