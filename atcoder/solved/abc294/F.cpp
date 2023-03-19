#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, m;
	int64_t k;
	cin >> n >> m >> k;
	k = int64_t(n) * m - k + 1;
	vector<pair<int, int>> A(n), B(m);
	//int maxa = 0, maxb = 0;
	for (auto& [a, b] : A)
	{
		cin >> a >> b;
		b += a;
		//maxa = max(maxa, b);
	}
	for (auto& [a, b] : B)
	{
		cin >> a >> b;
		b += a;
		//maxb = max(maxb, b);
	}

	/*
	vector<vector<int>> X(maxa + 1), Y(maxb + 1);
	for (auto [a, b] : A)
		X[b].push_back(a);
	for (auto [a, b] : B)
		Y[b].push_back(a);*/

	vector<long double> AA(n);

	long double lo = 0, hi = 1;
	while (hi - lo >= 5e-12l)
	{
		long double z = (lo + hi) / 2;
		for (int i = 0; i < n; i++)
			AA[i] = A[i].first - z * A[i].second;
		sort(begin(AA), end(AA));
		int64_t ans = 0;
		for (int i = 0; i < m; i++)
		{
			long double t = z * B[i].second - B[i].first;
			ans += upper_bound(begin(AA), end(AA), t) - begin(AA);
		}
		//cerr << fixed << setprecision(11) << z * 50 << ' ' << ans << endl;
		if (ans >= k)
			hi = z;
		else
			lo = z;
	}
	cout << fixed << setprecision(11) << (lo + hi) * 50;
}