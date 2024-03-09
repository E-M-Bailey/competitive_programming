#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	n++;
	vector<pair<int, int>> A(n);
	vector<int> B(n);
	for (int i = 0; i < n; i++)
	{
		cin >> B[i];
		A[i] = { B[i], i };
	}
	sort(begin(A), end(A));
	int t = 0;
	int ans = 0;
	for (int j = 0; j < n; j++)
	{
		int i = A[j].second;
		if (i <= j)
			continue;
		if (i == 0 || B[i - 1] > B[i])
			t = 1 - i % 2;
		else
			t++;
		ans = max(ans, t + i - j);
	}
	for (int j = n; j-- > 0;)
	{
		int i = A[j].second;
		if (i >= j)
			continue;
		if (i == n - 1 || B[i + 1] < B[i])
			t = i % 2;
		else
			t++;
		ans = max(ans, t + j - i);
	}
	cout << ans;
}