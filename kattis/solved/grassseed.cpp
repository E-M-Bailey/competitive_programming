#include <bits/stdc++.h>

using namespace std;

int main()
{
	double c, ans = 0;
	int	   n;
	cin >> c >> n;
	while (n--)
	{
		double w, l;
		cin >> w >> l;
		ans += w * l;
	}
	cout << fixed << setprecision(7) << ans * c;
}
