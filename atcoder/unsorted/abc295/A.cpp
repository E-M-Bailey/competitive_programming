#include <bits/stdc++.h>
using namespace std;

const unordered_set<string> D{"and", "not", "that", "the", "you"};

int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		string s;
		cin >> s;
		if (D.find(s) != D.end())
		{
			cout << "Yes\n";
			return 0;
		}
	}
	cout << "No\n";
}