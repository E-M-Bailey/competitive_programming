#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin >> s;
	int n = size(s), a = 0, b = 0, i = 0, j;
	(s[0] == s[j = --n] ? b : a) = 1e9;
	for (; ++i < --j;)
		tie(a, b) = s[i] == s[j] ? pair(min(a, b + 2), min(a + 2, b + 1)) : pair(min(a + 2, b + 1), min(a, b + 1));
	cout << min(a, b + 1);
}
