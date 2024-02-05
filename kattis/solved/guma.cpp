#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<int> HP(100001);
	for (int i = 2; i <= 100000; i++)
		if (!HP[i])
			for (int j = i; j <= 100000; j += i)
				HP[j] = i;

	int n;
	cin >> n;
	n++;

	bitset<100001> D{};
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		for (int j = 1; j * j <= a; j++)
			if (a % j == 0)
				D[j] = D[a / j] = true;
	}
	int64_t ans = 0;
	for (int d = 2; d <= 100000; d++)
		if (D[d])
		{
			int phi = d;
			for (int d2 = d; d2 > 1;)
			{
				int p = HP[d2];
				phi	  = phi / p * (p - 1);
				do
					d2 /= p;
				while (d2 % p == 0);
			}
			ans += phi;
		}
	cout << ans;
}
