#include <bits/stdc++.h>

using namespace std;

int main()
{
	int a, b;
	cin >> a >> b;
	for (int i = min(a, b); i <= max(a, b); i++)
		cout << i + 1 << '\n';
}
