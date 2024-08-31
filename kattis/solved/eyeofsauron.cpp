#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int ans = 0;
	for (char c : s)
		if (c == '|')
			ans++;
		else if (c == ')')
			ans = -ans;
	cout << (ans ? "fix" : "correct");
}
