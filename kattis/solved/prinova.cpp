#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> X(n);
	for (int &x : X)
		cin >> x;
	int a, b;
	cin >> a >> b;
	if (a % 2 == 0)
		a++;
	if (b % 2 == 0)
		b--;

	sort(begin(X), end(X));

	int da = INT_MAX, db = INT_MAX;
	for (int x : X)
	{
		da = min(da, abs(a - x));
		db = min(db, abs(b - x));
	}

	int ans = db > da ? b : a, d = max(db, da);

	for (int i = 1; i < (int)size(X); i++)
	{
		int l = X[i - 1], r = X[i];
		int m = (l + r) / 2;
		if (m < a)
			m = a;
		else if (m > b)
			m = b;
		else if (m % 2 == 0)
			m--;
		if (m < l || m > r)
			continue;
		int cd = min(m - l, r - m);
		if (cd > d)
		{
			ans = m;
			d	= cd;
		}
	}
	cout << ans;
}
