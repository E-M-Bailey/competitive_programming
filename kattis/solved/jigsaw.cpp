#include <bits/stdc++.h>

using namespace std;

int main()
{
	long long c, e, m;
	cin >> c >> e >> m;
	if (e % 2 || c != 4)
	{
		cout << "impossible";
		return 0;
	}
	long long w = (long long)roundl(e / 4.l - sqrtl((long double)e * e / 16 - m));
	long long h = e / 2 - w;
	if (w * 2 + h * 2 == e && w * h == m)
		cout << h + 2 << ' ' << w + 2;
	else
		cout << "impossible";
}
