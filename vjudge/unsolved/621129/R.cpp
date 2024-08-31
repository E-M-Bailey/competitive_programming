#include <bits/stdc++.h>

using namespace std;

int main()
{
	int SUM[10001]{};
	for (int n = 1; n <= 10000; n++)
	{
		int N	= n;
		int phi = 1;
		for (int p = 2; p * p <= N; p++)
			if (N % p == 0)
			{
				phi *= p - 1;
				N /= p;
				while (N % p == 0)
				{
					phi *= p;
					N /= p;
				}
			}
		if (N > 1)
			phi *= N - 1;
		SUM[n] = SUM[n - 1] + phi;
	}

	int p;
	cin >> p;
	while (p--)
	{
		int k, n;
		cin >> k >> n;
		cout << k << ' ' << SUM[n] * 3 - 1 << "/2\n";
	}
}
