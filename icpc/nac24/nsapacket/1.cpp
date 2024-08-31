#include <bits/stdc++.h>

using namespace std;

int main()
{
	for (;;)
	{
		string s;
		cin >> s;
		for (int i = 0; i < 26; i++)
		{
			cout << char('A' + i) << ": ";
			for (char &c : s)
				if (c++ == 'z')
					c = 'a';
			cout << s << endl;
		}
		cout << endl;
	}
}
