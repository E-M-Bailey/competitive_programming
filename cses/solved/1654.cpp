#include <bits/stdc++.h>

using namespace std;

int const N = 1 << 20;

void sos(vector<int> &A)
{
	vector<int> B(N);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < N; j++)
		{
			B[j] = A[j];
			if (j & (1 << i))
				B[j] += A[j ^ (1 << i)];
		}
		A.swap(B);
	}
}

int main()
{
	vector<int> A(N), B(N);
	int n;
	cin >> n;
	vector<int> X(n);
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		X[i] = x;
		A[x]++;
		B[(N - 1) ^ x]++;
	}
	sos(A);
	sos(B);
	for (int x : X)
		cout << A[x] << ' ' << B[(N - 1) ^ x] << ' ' << n - A[(N - 1) ^ x] << '\n';
}
