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
	int x, y;
	cin >> x >> y;
	int ans = 0;
	while (x || y)
	{
		int sp = 15;
		int cy = min(y, 2);
		y -= cy;
		sp -= cy * 4;
		int cx = min(sp, x);
		x -= cx;
		ans++;
	}
	cout << ans << '\n';

}
