#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	string t;
	for (char c : s)
	{
		if (t.empty() || t.back() != c)
			t.push_back(c);
		if (t.size() == 4)
			t.resize(2);
	}
	cout << t;
}
