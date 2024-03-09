#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> C(n);
	vector<vector<int>> S(n);
	for (int i = 0; i < n; i++)
	{
		int p;
		cin >> C[i] >> p;
		S[i].resize(p);
		for (int &s : S[i])
			cin >> s;
	}

	typedef double T;
	vector<T> DP(m);
	for (int i = 0; i < m; i++)
	{
		auto &dp = DP[i] = numeric_limits<T>::infinity();
		for (int j = 0; j < n; j++)
		{
			// x = (z x + b) / p + c = z/p x + b/p + c
			// x = (b + pc)/(p-z)

			int a = (int)S[j].size();
			T cur = a * C[j];
			for (int s : S[j])
			{
				if (s == 0)
					a--;
				else if (s <= i)
					cur += DP[i - s];
			}
			dp = min(dp, cur / a);
		}
	}
	cout << fixed << setprecision(6) << DP[m - 1];
}