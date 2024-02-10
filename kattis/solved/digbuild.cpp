#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1000000007;

int const M[]{0, 1, 2, 4, 5};

typedef array<int, 5> vec;
typedef array<vec, 5> mat;

mat mul(mat X, mat Y)
{
	mat Z{};
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				Z[i][j] = int((Z[i][j] + (int64_t)X[i][k] * Y[k][j]) % MOD);
	return Z;
}

int main()
{
	int64_t n;
	cin >> n;

	mat A{}, B{};
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
		{
			A[i][j] = (M[i] & M[j]) == 0;
			B[i][j] = i == j;
		}

	for (; n; n /= 2, A = mul(A, A))
		if (n % 2)
			B = mul(B, A);

	cout << accumulate(begin(B[0]), end(B[0]), 0ll) % MOD;
}
