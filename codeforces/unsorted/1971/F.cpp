#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	long long R;
	cin >> R;
	long long ans = 0, l = 0, r = 0;
	for (long long x = R; x > 0; x--)
	{
		while (r * r + x * x < (R + 1) * (R + 1))
			r++;
		while (l * l + x * x < R * R)
			l++;
		ans += r - l;
	}
	cout << ans * 4 << '\n';
}
