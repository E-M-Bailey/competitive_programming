#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	getline(cin, s);
	int ans = 0;
	for (char c : s)
		ans += ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
	cout << ans;
}
