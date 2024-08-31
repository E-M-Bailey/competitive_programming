#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, h, c;
	cin >> n >> h >> c;

	vector<int> A(h);
	vector<vector<int>> B(h, vector<int>(n));
	for (int i = 0; i < n; i++)
	{
		for (int &a : A)
			cin >> a;
		sort(begin(A), end(A));
		for (int j = 0; j < h; j++)
			B[j][i] = A[j];
	}

	int ans = 0;
	for (auto &BB : B)
	{
		sort(begin(BB), end(BB));
		for (int b : BB)
		{
			c -= b;
			if (c < 0)
				break;
			ans++;
		}
		if (c < 0)
			break;
	}

	cout << ans;
}
