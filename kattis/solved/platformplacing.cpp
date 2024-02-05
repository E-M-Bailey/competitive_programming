#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, s, k;
	cin >> n >> s >> k;
	vector<int> X(n);
	for (int &x : X)
		cin >> x;
	sort(begin(X), end(X));
	int a = k, b = k, y = s;

	const auto f = [&a, &y, s](int x)
	{
		return y - s + min(x, a);
	};
	for (int i = 1; i < n; i++)
	{
		int d = 2 * (X[i] - X[i - 1]);
		if (2 * s > d)
		{
			cout << -1;
			return 0;
		}
		y = s + f(min(b, d - s));
		b = min(k, d - s);
		a = max(min(d - a, b), s);
	}
	cout << f(a);
}
