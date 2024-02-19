#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string s, t;
	getline(cin, s);
	getline(cin, t);
	auto i = s.find('|'), j = t.find('|');
	cout << s.substr(0, i) << t.substr(0, j) << ' ' << s.substr(i + 1) << t.substr(j + 1);
}
