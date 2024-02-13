#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c = 0;
	cin >> a >> b;
	for (char ch; cin >> ch;)
		c += ch == '.';
	cout << fixed << setprecision(6) << (double)c / (a * b);
}
