#include <bits/stdc++.h>

using namespace std;
using namespace string_literals;

int main()
{
	string s, t = "123456789"s;
	cin >> s;
	if (t.find(s) == 0)
		cout << size(s);
	else
		cout << -1;
}
