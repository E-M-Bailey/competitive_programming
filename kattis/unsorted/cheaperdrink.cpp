#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<string> S(n);
	for (auto &s : S)
	{
		cin >> s;
		bool good = true;
		string s2 = s;
		for (char &c : s2)
		{
			if (c == '0' || c == '1' || c == '8')
				continue;
			else if (c == '6')
				c = '9';
			else if (c == '9')
				c = '6';
			else
			{
				good = false;
				break;
			}
		}
		reverse(begin(s2), end(s2));
		if (good && s2 < s)
			s = move(s2);
	}
	sort(begin(S), end(S), [&](string const &a, string const &b)
		{
			return a + b < b + a;
		});
	for (string s : S)
		cout << s;
}