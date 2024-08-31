#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<string> S(n);
	int			   ans = 0;
	for (string &s : S)
	{
		cin >> s;
		for (char &c : s)
			c |= 32;
		ans += s.find("pink") != string::npos || s.find("rose") != string::npos;
	}
	if (ans)
		cout << ans;
	else
		cout << "I must watch Star Wars with my daughter";
}
