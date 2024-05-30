#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	set<string> S{"keys", "phone", "wallet"};
	while (n--)
	{
		string s;
		cin >> s;
		S.erase(s);
	}
	for (string const &s : S)
		cout << s << '\n';
	if (S.empty())
		cout << "ready";
}
