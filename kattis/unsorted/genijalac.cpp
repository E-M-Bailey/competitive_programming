#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	int64_t a, b;
	int c, d;
	cin >> n >> a >> b >> c >> d;
	a--;
	d = n - d;
	vector<int> P(n);
	for (int &p : P)
	{
		cin >> p;
		p--;
	}
	vector<bool> vis(n);
	int64_t lcm = 1;
	for (int i = 0; i < n; i++)
	{
		int64_t cur = 0;
		bool needed = false;
		for (int j = i; !vis[j]; j = P[j])
		{
			vis[j] = true;
			cur++;
			needed |= c <= j && j < d;
		}
		if (needed)
		{
			lcm *= cur / gcd(cur, lcm);
			if (lcm >= b)
				break;
		}
	}
	cout << (b + lcm - 1) / lcm - (a + lcm - 1) / lcm;
}