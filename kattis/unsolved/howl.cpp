#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	string t = "AWAWHO";
	while (t.size() <= s.size())
		t += 'O';
	cout << t;
}