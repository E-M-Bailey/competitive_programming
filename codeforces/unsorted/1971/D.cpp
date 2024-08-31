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
	bool used = false;
	int	 ans  = 1;
	for (int i = 1; i < (int)size(s); i++)
	{
		if (!used && s[i - 1] == '0' && s[i] == '1')
			used = true;
		else if (s[i - 1] != s[i])
			ans++;
	}
	cout << ans << '\n';
}
