#include <bits/stdc++.h>

using namespace std;

int main()
{
	string s;
	cin >> s;
	int n = (int)size(s) / 2;
	int sum = accumulate(begin(s), end(s), -2 * n * 'A');
	for (int i = 0; i < n; i++)
		s[i] = char((s[i] + s[i + n] + sum - 2 * 'A') % 26 + 'A');
	s.resize(n);
	cout << s;
}
