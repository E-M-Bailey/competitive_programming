#include <bits/stdc++.h>

using namespace std;

int main()
{
	string				  s;
	bool				  ans = true;
	unordered_set<string> S;
	while (cin >> s)
		ans &= S.insert(s).second;
	cout << (ans ? "yes" : "no");
}
