#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	ostringstream strm;
	string		  S;
	while (cin >> S)
	{
		int			   n = (int)size(S);
		vector<string> ans;
		ans.reserve(n * (n - 1) / 2);
		for (int i = 0; i < n; i++)
		{
			int a = i - 1, b = i + 1;
			while (a >= 0 && b < n && S[a] == S[b])
			{
				ans.push_back(S.substr(a, b - a + 1));
				a--;
				b++;
			}
		}
		for (int i = 0; i < n - 1; i++)
		{
			int a = i, b = i + 1;
			while (a >= 0 && b < n && S[a] == S[b])
			{
				ans.push_back(S.substr(a, b - a + 1));
				a--;
				b++;
			}
		}
		sort(begin(ans), end(ans));
		ans.resize(unique(begin(ans), end(ans)) - begin(ans));
		for (const string &s : ans)
			strm << s << '\n';
		strm << '\n';
	}
	cout << strm.str();
}
