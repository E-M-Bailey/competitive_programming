#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1e9 + 7;

template<size_t N, size_t K, size_t M>
array<array<int64_t, M>, N> operator*(array<array<int64_t, K>, N> const &A, array<array<int64_t, M>, K> const &B)
{
	array<array<int64_t, M>, N> C{};
	for (size_t i = 0; i < N; i++)
		for (size_t j = 0; j < M; j++)
			for (size_t k = 0; k < K; k++)
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
	return C;
}

template<size_t N>
array<array<int64_t, N>, N> mpow(array<array<int64_t, N>, N> A, int64_t b)
{
	array<array<int64_t, N>, N> B{};
	for (size_t i = 0; i < N; i++)
		B[i][i] = 1;
	do
		if (b % 2)
			B = B * A;
	while (A = A * A, b /= 2);
	return B;
}

int main()
{
	int64_t n;
	cin >> n;

	array<array<int64_t, 3>, 3> M{array<int64_t, 3>{1, 1, 1}, array<int64_t, 3>{1, 0, 0}, array<int64_t, 3>{0, 0, 1}};
	array<array<int64_t, 1>, 3> X{array<int64_t, 1>{2}, array<int64_t, 1>{1}, array<int64_t, 1>{1}},
		Y = mpow(M, n - 1) * X;
	cout << Y[1][0];
}
