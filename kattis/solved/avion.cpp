#include <bits/stdc++.h>

using namespace std;

int main()
{
	bool f = false;
	for (int i = 0; i < 5; i++)
	{
		string s;
		cin >> s;
		if (s.find("FBI") != string::npos)
		{
			f = true;
			cout << i + 1 << ' ';
		}
	}
	if (!f)
		cout << "HE GOT AWAY!";
}
