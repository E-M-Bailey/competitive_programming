#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
	{
		int	   k;
		string s;
		cin >> k >> s;
		auto pos = s.find('/');
		int	 p = stoi(s.substr(0, pos)), q = stoi(s.substr(pos + 1));

		int ans = 0, p2 = 1;
		while (p)
		{
			if (p < q)
				q -= p;
			else
			{
				p -= q;
				ans += p2;
			}
			p2 *= 2;
		}

		cout << k << ' ' << ans << '\n';
	}
}
