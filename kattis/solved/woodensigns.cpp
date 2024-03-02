#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	int s;
	cin >> n >> s;
	s--;

	vector<int> A(n);
	for (int &a : A)
	{
		cin >> a;
		a--;
	}

	vector<int64_t> X(n + 1), Y = X;
	X[s] = 1;

	for (int i = 1; i < n; i++)
	{
		int a = A[i - 1], b = A[i];
		for (int j = 0; j <= n; j++)
		{
			auto [l, r] = minmax(a, j);
			if (b > l)
				Y[l] += X[j];
			if (b < r)
				Y[r] += X[j];
		}
		for (int j = 0; j <= n; j++)
		{
			X[j] = Y[j] % INT_MAX;
			Y[j] = 0;
		}
	}

	cout << accumulate(begin(X), end(X), (int64_t)0) % INT_MAX;
}
