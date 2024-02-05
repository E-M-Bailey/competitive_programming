#include <bits/stdc++.h>

using namespace std;

vector<int> readClock(int n)
{
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	sort(begin(A), end(A));
	vector<int> B(n);
	B.front() = A.front() - A.back() + 360000;
	for (int i = 1; i < n; i++)
		B[i] = A[i] - A[i - 1];
	return B;
}

vector<int> zArray(const vector<int> &A)
{
	int			n = A.size();
	vector<int> Z(n);
	int			l = 0, r = 0;

	for (int i = 1; i < n; i++)
	{
		if (i <= r)
			Z[i] = min(r - i + 1, Z[i - l]);
		while (i + Z[i] < n && A[Z[i]] == A[i + Z[i]])
			Z[i]++;
		if (i + Z[i] - 1 > r)
			l = i, r = i + Z[i] - 1;
	}
	return Z;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	vector<int> A = readClock(n);
	vector<int> B = readClock(n);
	A.resize(3 * n + 1);
	for (int i = 0; i < n; i++)
		A[i + n + 1] = A[i + 2 * n + 1] = B[i];
	A[n]			= -1;
	vector<int> Z	= zArray(A);
	bool		ans = false;

	for (int i = n + 1; !ans && i < 3 * n + 1; i++)
		if (Z[i] == n)
			ans = true;
	cout << (ans ? "possible" : "impossible");
}
