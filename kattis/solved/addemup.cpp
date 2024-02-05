#include <bits/stdc++.h>

using namespace std;

bitset<1'000'000'001> S{};

int main()
{
	int n, s;
	cin >> n >> s;
	while (n--)
	{
		string str;
		cin >> str;
		int a = atoi(str.c_str());
		if (a <= s && S[s - a])
		{
			cout << "YES\n";
			return 0;
		}
		reverse(begin(str), end(str));
		bool good = true;
		for (char &c : str)
		{
			if (c == '6')
				c = '9';
			else if (c == '9')
				c = '6';
			else if (c == '3' || c == '4' || c == '7')
				good = false;
		}
		if (good)
		{
			int b = atoi(str.c_str());
			if (b <= s && S[s - b])
			{
				cout << "YES\n";
				return 0;
			}
			S[b] = true;
		}
		S[a] = true;
	}
	cout << "NO\n";
}
