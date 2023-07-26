#include <bits/stdc++.h>

using namespace std;

int FS[26];

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(0);

	string pr;
	int n;
	cin >> pr >> n;
	char st = pr.back();

	vector<string> S(n);
	for (string &s : S)
	{
		cin >> s;
		++FS[s.front() - 'a'];
	}

	char const *ans = "?";
	for (string const &s : S)
	{
		if (s.front() != st)
			continue;
		char nx = s.back();
		if (FS[nx - 'a'] == (nx == st))
		{
			cout << s << '!';
			return 0;
		}
		if (*ans == '?')
			ans = s.c_str();
	}
	cout << ans;
}