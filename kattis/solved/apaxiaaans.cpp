#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	s.erase(unique(begin(s), end(s)), end(s));
	cout << s;
}
