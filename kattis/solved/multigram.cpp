#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int					   n = (int)size(s);
	vector<array<int, 26>> P(n + 1);
	for (int i = 0; i < n; i++)
	{
		P[i + 1] = P[i];
		P[i + 1][s[i] - 'a']++;
	}

	auto const qry = [&](int l, int r)
	{
		array<int, 26> ans{};
		for (int i = 0; i < 26; i++)
			ans[i] = P[r][i] - P[l][i];
		return ans;
	};

	for (int l = 1; l < n; l++)
		if (n % l == 0)
		{
			auto cur  = qry(0, l);
			bool good = true;
			for (int i = l; good && i < n; i += l)
				good &= qry(i, i + l) == cur;
			if (good)
			{
				cout << s.substr(0, l);
				return 0;
			}
		}
	cout << "-1";
}
