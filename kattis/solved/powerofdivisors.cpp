#include <bits/stdc++.h>

using namespace std;

int powof(long long a, long long b)
{
	int ans = 0;
	while (b > 1)
	{
		if (b % a)
			return -1;
		b /= a;
		ans++;
	}
	return ans;
}

int main()
{
	long long x;
	cin >> x;

	vector<int> HP(1000001);
	vector<int> P;
	for (int i = 2; i < 1000001; i++)
		if (!HP[i])
		{
			P.push_back(i);
			for (int j = i; j < 1000001; j += i)
				HP[j] = i;
		}

	long long s = (long long)roundl(sqrtl(x));

	bool ps = s >= 2 && s * s == x;
	for (int i = 0, p; ps && (p = P[i], p * p <= s); i++)
		ps &= s % p != 0;

	if (x == 1)
		cout << 1;
	else if (ps)
		cout << s;
	else
	{
		for (int n = 4; n < 1000001; n++)
		{
			int pw = 1;
			for (int n2 = n; n2 > 1;)
			{
				int cur = 1, p = HP[n2];
				do
				{
					cur++;
					n2 /= p;
				} while (HP[n2] == p);
				pw *= cur;
			}
			if (powof(n, x) == pw)
			{
				cout << n;
				return 0;
			}
		}
		cout << -1;
	}
}