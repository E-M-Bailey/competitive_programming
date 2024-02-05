#include <bits/stdc++.h>

using namespace std;

int main()
{
	long long n, k, p, a = 1;
	cin >> n >> k >> p;
	vector<long long> X;
	for (; a * a <= n; a++)
	{
		long long b = n / a;
		if (a * b != n)
			continue;
		if (a <= k && b <= p)
			X.push_back(a);
		if (a != b && a <= p && b <= k)
			X.push_back(b);
	}
	sort(begin(X), end(X));

	cout << X.size() << '\n';
	for (auto x : X)
		cout << x << '\n';
}
