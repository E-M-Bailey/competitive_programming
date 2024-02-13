#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, a, num = 0;
	cin >> n;
	while (n--)
	{
		cin >> a;
		for (int i = 1; i <= 6; i++)
			for (int j = 1; j <= 6; j++)
				num += a == i + j;
	}
	cout << fixed << setprecision(6) << num / 36.;
}
