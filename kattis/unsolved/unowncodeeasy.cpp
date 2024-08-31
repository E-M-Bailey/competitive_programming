#include <bits/stdc++.h>

using namespace std;

int mpow(int a, int b, int m)
{
	int ans = 1;
	for (; b; a = int((long long)a * a % m), b /= 2)
		if (b % 2)
			ans = int((long long)ans * a % m);
	return ans;
}

int ord2(int a, int x)
{
	
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	int ax = 1, ay = 1;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		int k = (int)size(s);
		int a = stoi(s), a2 = a;
		int x = __builtin_ctz(a), y = 0;
		a2 >>= x;
		while (a2 % 5 == 0)
		{
			y++;
			a2 /= 5;
		}
		int X = max(0, k - x), Y = max(0, k - y);
		if ((X && x) || (Y && y))
		{
			cout << "-1";
			return 0;
		}

		int M = 1 << X;
		for (int j = 0; j < Y; j++)
			M *= 5;

		if (X)
			X--;
		if (Y)
		{
			Y--;
			X += 2;
		}

		int cur = INT_MAX;
		for (int b = 0, B = 1; b <= Y; b++, B *= 5)
		{
			int lo = 0, hi = X + 1;
			while (lo < hi)
			{
				int aa = (lo + hi) / 2;
				if (mpow(a, B << aa, M) == 1)
				{
					cur = min(cur, B << aa);
					hi = aa;
				}
				else
					lo = aa + 1;
			}
		}
		ans = lcm(ans, (long long)cur);
	}

	cout << ans + 1;
}
