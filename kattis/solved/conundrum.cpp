#include <bits/stdc++.h>

using namespace std;

int main()
{
	int	   ans = 0;
	string s;
	cin >> s;
	for (int i = 0; i < (int)size(s); i++)
		ans += s[i] != "PER"[i % 3];
	cout << ans;
}
