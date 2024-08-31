#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	string s;
	cin >> s;
	string r = s.substr(1) + s.front();
	if (r == s)
		cout << "NO\n";
	else
		cout << "YES\n" << r << '\n';
}
