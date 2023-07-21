/*
BEGIN ANNOTATION:
PROBLEM URL: https://open.kattis.com/problems/absolutelysymmetric
TAGS: matrix, matrices, math, parith
EXPLANATION:
Consider any pair of entries a = A[i,j], b = A[j,i].
For m = 1, 2, ..., k, call the corresponding entries in the answer am = Xm[i,j] and bm = Xm[j,i].
For all i, j, a = a1 + a2 + ... + an and b = b1 + b2 + ... + bk. Moreover, for all i, j, m, |am| = |bm|.

Note that if |am| = |bm|, then am and bm have the same parity, so am + bm is even.
Thus, a + b = a1 + ... + ak + b1 + ... + bk = (a1 + b1) + ... + (ak + bk) is even, so a and b must have the same parity.
If they don't, the answer is -1.


This can be accomplished with just one matrix iff |a| = |b|: a1 = a and b1 = b for all i, j.

Otherwise, this can be accomplished with two matrices: let a1 = b1 = (a + b) / 2 and a2 = -b2 = (a - b) / 2.
Since a and b have the same parity, these values are integers.
Moreover, a1 + a2 = (a + b + a - b) / 2 = a and b1 + b2 = (a + b - a + b) / 2 = b.
*/

#include <bits/stdc++.h>

using namespace std;

int A[50][50];

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> A[i][j];

	// Whether it's possible w/ 1 or 2 matrices, respectively
	bool one = true, two = true;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			int a = A[i][j], b = A[j][i];
			// k = 1: |a| = |b| for all i, j.
			one &= abs(a) == abs(b);
			// k <= 2: a and b must have the same parity.
			two &= ((a ^ b) & 1) == 0;
		}

	if (one)
	{
		// k = 1
		cout << "1\n";
		// a1 = a
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cout << A[i][j] << ' ';
			cout << '\n';
		}
	}
	else if (two)
	{
		// k = 2
		cout << "2\n";
		// a1 = (a + b) / 2
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cout << (A[i][j] + A[j][i]) / 2 << ' ';
			cout << '\n';
		}
		// a2 = (a - b) / 2
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				cout << (A[i][j] - A[j][i]) / 2 << ' ';
			cout << '\n';
		}
	}
	else
		// No Solution
		cout << "-1";
}