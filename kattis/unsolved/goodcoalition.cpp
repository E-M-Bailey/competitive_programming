#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n;
		cin >> n;
		double P[151]{};
		P[0] = 1;
		while (n--)
		{
			int	   x;
			double p;
			cin >> x >> p;
			p /= 100;
			for (int i = 150; i >= x; i--)
				P[i] = max(P[i], P[i - x] * p);
		}

		cout << fixed << setprecision(8) << 100 * *max_element(P + 76, P + 151) << '\n';
	}
}