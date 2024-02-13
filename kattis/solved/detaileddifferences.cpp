#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	while (n--)
	{
		string a, b;
		cin >> a >> b;
		cout << a << '\n' << b << '\n';
		for (int i = 0; i < (int)size(a); i++)
			cout << (a[i] == b[i] ? '.' : '*');
		cout << "\n\n";
	}
}
