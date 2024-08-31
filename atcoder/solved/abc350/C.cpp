#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> A(n), B(n);
	vector<pair<int, int>> ans;
	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
		B[--A[i]] = i;
	}

	for (int i = 0; i < n; i++)
	{
		int j = A[i], pi = B[i];
		if (i == j)
			continue;
		swap(A[pi], A[i]);
		swap(B[i], B[j]);
		ans.emplace_back(i + 1, pi + 1);
	}
	cout << size(ans) << '\n';
	for (auto [i, j] : ans)
	{
		cout << i << ' ' << j << '\n';
	}
}
