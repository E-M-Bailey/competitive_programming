#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> A;

int left() // skip A[0]
{
	int s = A[1] + A[m - 1];
	if (s <= A[0])
		return INT_MAX;
	for (int i = 2, j = m - 2; i < j; i++, j--)
		if (A[i] + A[j] != s)
			return INT_MAX;
	return s - A[0];
}

int right() // skip A[m - 1]
{
	int s = A[0] + A[m - 2];
	if (s <= A[m - 1])
		return INT_MAX;
	for (int i = 1, j = m - 3; i < j; i++, j--)
		if (A[i] + A[j] != s)
			return INT_MAX;
	return s - A[m - 1];
}

int mid()
{
	int s = A[0] + A[m - 1];
	int ans = 0;
	for (int i = 1, j = m - 2; i < j; i++, j--)
	{
		if (A[i] + A[j] > s) // skip A[j]
		{
			if (ans || s <= A[j])
				return INT_MAX;
			ans = s - A[j];
			i--;
		}
		else if (A[i] + A[j] < s) // skip A[i]
		{
			if (ans || s <= A[i])
				return INT_MAX;
			ans = s - A[i];
			j++;
		}
	}
	return ans ? : s <= A[m / 2] ? INT_MAX : s - A[m / 2];
}

int main()
{
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++)
	{
		cout << "Case #" << tt << ": ";
		cin >> n;
		m = 2 * n - 1;
		A.resize(m);
		for (int &a : A)
			cin >> a;

		if (n == 1)
		{
			cout << "1\n";
			continue;
		}
		sort(begin(A), end(A));

		int best = min({ left(), right(), mid() });
		cout << (best == INT_MAX ? -1 : best) << '\n';
	}
}
