#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int	   n, k;
		string s;
		cin >> n >> k >> s;
		if (n <= k)
		{
			cout << "-1\n";
			continue;
		}

		set<int> S;
		for (int i = 0; i < n; i++)
			if (s[i] == '#')
				S.insert(i);
		
		int ans = 0;
		for (;;)
		{
			bool succ = true;
			int pos = -1;
			while (pos + k + 1 < n)
			{
				int lim = pos + k + 1;
				auto it = S.upper_bound(lim);
				it = (it == begin(S) ? end(S) : prev(it));
				if (it == end(S) || *it < pos)
				{
					succ = false;
					break;
				}
				pos = *it;
				S.erase(it);
			}

			if (!succ)
				break;
			ans++;
		}
		cout << ans << '\n';
	}
}