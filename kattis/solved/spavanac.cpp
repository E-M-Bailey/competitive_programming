#include <bits/stdc++.h>

using namespace std;

int main()
{
	int h, m;
	cin >> h >> m;
	int t = h * 60 + m;
	t += 24 * 60 - 45;
	if (t >= 24 * 60)
		t -= 24 * 60;
	cout << t / 60 << ' ' << t % 60;
}
