#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, l;
	cin >> n >> l;
	vector<long double> X(n);
	for (long double& x : X)
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
				//cerr << a << ' ' << b << endl;
				P.emplace_back(a, -1);
				P.emplace_back(b, 1);
			}
		}
	P.emplace_back(10, -1);
	P.emplace_back(INF, 1);
	P.emplace_back(0, -1);
	P.emplace_back(.1l, 1);
	sort(begin(P), end(P), greater<>());
	//for (auto [p, c] : P)
	//	cerr << p << ' ';
	//cerr << endl;
	/*
	if (P.empty() || P.back().first >= 10 || P.front().first <= 10)
	{
		cout << 10;
		return 0;
	}*/

	int ct = 0;
	for (int i = 1; i < (int)P.size(); i++)
	{
		ct += P[i - 1].second;
		//cerr << ct << endl;
		if (ct == 0)
		{
			//long double a = max(P[i].first, .1l), b = min(P[i - 1].first, 10.l);
			long double a = P[i].first, b = P[i - 1].first;
			//cerr << ' ' << a << ' ' << b << ' ' << ct << endl;
			//if (a <= b)
			//{
			cout << fixed << setprecision(10) << b;
			return 0;
			//}
		}
	}

	cout << "no fika";
}