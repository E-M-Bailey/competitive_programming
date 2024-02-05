#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	vector<int> A(n);
	for (int &a : A)
	{
		char c;
		cin >> c;
		a = c - '0';
	}
	int i = 0, ans = 0;
	for (int i = 0; i < n; i++)
	{
		if (!A[i])
			continue;
		ans++;
		A[i] = 0;
		if (i < n - 2)
		{
			A[i + 2] |= A[i + 1];
			A[i + 1] = 0;
		}
	}

	cout << ans;
}
