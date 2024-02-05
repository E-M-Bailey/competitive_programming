#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, l;
	cin >> n >> l;
	vector<long double> X(n);
	for (long double &x : X)
		cin >> x;

	sort(begin(X), end(X));

	const long double INF = numeric_limits<long double>::infinity();

	vector<pair<long double, int>> P;

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
		{
			long double d = X[j] - X[i];
			for (int k = 0; k <= 11 * d + 1; k += l)
			{
				long double a = d / (k + 1), b = k <= 1 ? INF : d / (k - 1);
				P.emplace_back(a, -1);
				P.emplace_back(b, 1);
			}
		}
	P.emplace_back(10, -1);
	P.emplace_back(INF, 1);
	P.emplace_back(0, -1);
	P.emplace_back(.1l, 1);
	sort(begin(P), end(P), greater<>());

	int ct = 0;
	for (int i = 1; i < (int)P.size(); i++)
	{
		ct += P[i - 1].second;
		if (ct == 0)
		{
			long double a = P[i].first, b = P[i - 1].first;
			cout << fixed << setprecision(10) << b;
			return 0;
		}
	}

	cout << "no fika";
}
