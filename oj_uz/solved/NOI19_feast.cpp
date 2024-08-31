#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n, k;
	cin >> n >> k;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	int64_t lo = 0, hi = 3e14l;
	int64_t ans = INT64_MAX;
	while (lo < hi)
	{
		int64_t lam = (lo + hi) / 2;
		pair<int64_t, int> a{0, 0}, b{ INT64_MAX / 2, 0 };
		for (int i = 0; i < n; i++)
		{
			auto temp = min(a, b);
			a.first += lam - A[i];
			a.second++;
			b.first -= A[i];
			b = min(a, b);
			a = temp;
		}

		a = min(a, b);
		if (a.second > k)
			lo = lam + 1;
		else
		{
			hi = lam;
			ans = a.first - a.second * lam;
		}
	}
	cout << -ans;
}