#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	long long s, p;
	int		  m, n;
	cin >> s >> p >> m >> n;

	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	vector<long long> DP(n + 1);
	for (int i = 0, j = 0; i < n; i++)
	{
		int a = A[i];
		// A[j] <= a - m
		while (j == 0 ? -m : A[j - 1] <= a - m)
			j++;
		j--;
		DP[i + 1] = min(DP[i] + s, DP[j] + p);
	}

	cout << DP.back();
}
