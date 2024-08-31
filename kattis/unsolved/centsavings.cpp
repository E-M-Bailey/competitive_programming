#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, d;
	cin >> n >> d;
	vector<array<int, 10>> A(d + 1);
	for (int i = 0; i <= d; i++)
		fill(begin(A[i]) + 1, end(A[i]), INT_MAX / 2);
	int s = 0;

	for (int i = 0; i < n; i++)
	{
		int p;
		cin >> p;
		s += p;
		for (int j = 0; j <= d; j++)
			rotate(begin(A[j]), end(A[j]) - p % 10, end(A[j]));
		for (int j = 1; j <= d; j++)
		{
			for (int c = 0; c < 5; c++)
				A[j][0] = min(A[j][0], A[j - 1][c] - c);
			for (int c = 5; c < 10; c++)
				A[j][0] = min(A[j][0], A[j - 1][c] + 10 - c);
		}
	}

	int ans = INT_MAX;
	for (int j = 0; j <= d; j++)
	{
		for (int c = 0; c < 5; c++)
			ans = min(ans, A[j][c] - c);
		for (int c = 5; c < 10; c++)
			ans = min(ans, A[j][c] + 10 - c);
	}

	cout << s + ans;
}
