#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		string s;
		cin >> s;
		cout << (s.front() == s.back() ? "NO\n" : "YES\n");
	}
}
