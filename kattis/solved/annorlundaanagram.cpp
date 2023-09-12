#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	vector<int> I[26];
	int n = (int)s.size();
	for (int i = 0; i < n; i++)
		I[s[i] - 'a'].push_back(i);

	for (auto const &II : I)
	{
		int m = (int)II.size();
		if (0 < m && m <= n / 2)
		{
			char c = s[II[0]];
			int lo = n / 2 - m / 2, hi = n / 2 + (m + 1) / 2;
			string t(n, c);
			for (int i = 0, j = 0; i < n; i++)
			{
				if (s[i] == c)
					continue;
				t[j++] = s[i];
				if (j == lo)
					j = hi;
			}
			cout << t;
			return 0;
		}
	}
	cout << "-1";
}