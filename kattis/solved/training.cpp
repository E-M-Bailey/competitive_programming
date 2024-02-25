#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, s;
	cin >> n >> s;
	while (n--)
	{
		int l, r;
		cin >> l >> r;
		s += l <= s && s <= r;
	}
	cout << s;
}
