#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	string s;
	cin >> s;
	int a = 0, b = 0;
	for (char c : s)
	{
		a += c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
		b += c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
	}
	cout << a << ' ' << b << '\n';
}