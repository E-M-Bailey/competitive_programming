#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	vector<int> ans;
	for (int k = 1; k <= s.size(); k++)
	{
		int A = 0, B = 0, a = 0, b = 0;
		for (char c : s)
		{
			if (c == 'A')
			{
				if (++a == k)
				{
					a = b = 0;
					A++;
				}
			}
			else
			{
				if (++b == k)
				{
					a = b = 0;
					B++;
				}
			}
		}
		if (A > B)
			ans.push_back(k);
	}
	cout << ans.size();
	if (!ans.empty())
	{
		cout << '\n';
		for (int k : ans)
			cout << k << ' ';
	}
}