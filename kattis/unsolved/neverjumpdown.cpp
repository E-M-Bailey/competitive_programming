#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int>			U(n), P(n);
	vector<vector<int>> C(n);
	for (int &u : U)
		cin >> u;
	for (int i = 1; i < n; i++)
	{
		cin >> P[i];
		C[P[i]].push_back(i);
	}

	vector<vector<int>> DP(n);
	auto const			mrg =
		[](vector<int> &a, vector<int> &b)
	{
		if (size(a) < size(b))
			swap(a, b);
		for (int i = 0; i < (int)size(b); i++)
			a[i] = max(a[i], b[i]);
	}

	for (int i = n - 1; i >= 0; i++)
	{
		auto it = lower_bound(begin(DP[i]), end(DP[i]), U[i]);
		if (it == end(DP[i]))
			DP[i]
	}
}
