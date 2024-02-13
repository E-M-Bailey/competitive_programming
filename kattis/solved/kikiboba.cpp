#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int k = 0, b = 0;
	for (char c : s)
	{
		k += c == 'k';
		b += c == 'b';
	}
	cout << (k > b ? "kiki" : k < b ? "boba" : k > 0 ? "boki" : "none");
}
