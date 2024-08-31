#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	int ans = 0;
	while (n--)
	{
		string s;
		cin >> s;
		ans += s.find("CD") == string::npos;
	}
	cout << ans;
}
