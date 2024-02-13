#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	sort(begin(s), end(s));
	cout << (unique(begin(s), end(s)) == end(s));
}
