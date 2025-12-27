#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, x, S = 0, M = 0, L = 0;
	cin >> n;
	for (char c; n--;)
	{
		cin >> c >> x;
		(c == 'S' ? S : c == 'M' ? M : L) += x;
	}
	cout << (S + 5) / 6 + (M + 7) / 8 + (L + 11) / 12;
}
