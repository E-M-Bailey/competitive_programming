#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	s = s.substr(3);
	int n = stoi(s);
	cout << (1 <= n && n <= 349 && n != 316 ? "Yes" : "No");
}

