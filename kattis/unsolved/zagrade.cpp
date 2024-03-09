#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int n = (int)s.size(), m = (int)count(begin(s), end(s), '(');
	int stck = 0;
	vector<string> ans((1 << m) - 1);
	for (int mask = 0; mask < (1 << m) - 1; mask++)
	{
		int pos = 0;
		for (char c : s)
		{
			if (c == '(')
			{
				int incl = (mask >> pos) & 1;
				pos++;
				if (incl)
					ans[mask].push_back(c);
				stck = (stck << 1) | incl;
			}
			else if (c == ')')
			{
				if (stck & 1)
					ans[mask].push_back(c);
				stck >>= 1;
			}
			else
				ans[mask].push_back(c);
		}
	}
	sort(begin(ans), end(ans));
	ans.erase(unique(begin(ans), end(ans)), end(ans));
	for (auto const &line : ans)
		cout << line << '\n';
}