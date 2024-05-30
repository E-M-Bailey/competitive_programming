#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s, t;
	cin >> s >> t;
	int ans = 1;
	for (int i = 0; i < (int)size(s); i++)
		ans += s[i] != t[i];
	cout << ans;
}
