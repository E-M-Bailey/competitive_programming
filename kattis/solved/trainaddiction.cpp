#include <bits/stdc++.h>

using namespace std;

const int MOD = 1'000'000'007;

struct bmat
{
	int					 m, n;
	vector<vector<bool>> A;
	bmat(int M, int N) : m(M), n(N), A(m, vector<bool>(n)) {}

	friend bmat operator*(bmat const &A, bmat const &B)
	{ // Assume A.n == B.m
		assert(A.n == B.m);
		bmat C(A.m, B.n);
		for (int i = 0; i < A.m; i++)
			for (int j = 0; j < B.n; j++)
				for (int k = 0; k < A.n; k++)
					C.A[i][j] = C.A[i][j] || (A.A[i][k] && B.A[k][j]);
		return C;
	}

	friend bmat mpow(bmat A, long long b)
	{
		// Assume A.m == A.n
		assert(A.m == A.n);
		bmat C(A.n, A.n);
		for (int i = 0; i < A.n; i++)
			C.A[i][i] = 1;

		for (; b; b /= 2, A = A * A)
			if (b % 2)
				C = C * A;
		return C;
	}
};

struct mat
{
	int					m, n;
	vector<vector<int>> A;
	mat(int M, int N) : m(M), n(N), A(m, vector<int>(n)) {}

	friend mat operator*(mat const &A, mat const &B)
	{
		// Assume A.n == B.m
		mat C(A.m, B.n);
		for (int i = 0; i < A.m; i++)
			for (int j = 0; j < B.n; j++)
			{
				for (int k = 0; k < A.n; k++)
					C.A[i][j] = (C.A[i][j] + (long long)A.A[i][k] * B.A[k][j]) % MOD;
			}
		return C;
	}

	friend mat mpow(mat A, long long b)
	{
		// Assume A.m == A.n
		mat C(A.n, A.n);
		for (int i = 0; i < A.n; i++)
			C.A[i][i] = 1;

		for (; b; b /= 2, A = A * A)
			if (b % 2)
				C = C * A;
		return C;
	}
};

// a(n): # ways to make a train of length n
// How many ways are there to make a train car ending with car i?
//    a(n - l_i)
// a(n) = sum_i a(n - l_i)
// (a(n - 1), a(n - 2), a(n - 3), a(n - 4))
// -> (a(n), a(n - 1), ... a(n - 3))
// a(n) = c1 a(n - 1) + ... + c4 a(n - 4)
// [c1 c2 c3 c4]
// [1  0  0  0]
// [0  1  0  0]
// [0  0  1  0]

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n, k;
		cin >> n >> k;

		mat	 M(50, 50);
		bmat B(50, 50);
		for (int i = 1; i < 50; i++)
		{
			M.A[i][i - 1] = 1;
			B.A[i][i - 1] = true;
		}

		for (int i = 0; i < k; i++)
		{
			int l;
			cin >> l;
			M.A[0][l - 1]++;
			B.A[0][l - 1] = true;
		}

		mat	 F(50, 1);
		bmat FB(50, 1);
		F.A[0][0]  = 1;
		FB.A[0][0] = true;

		F  = mpow(M, n) * F;
		FB = mpow(B, n) * FB;
		if (FB.A[0][0])
		{
			cout << F.A[0][0] << '\n';
		}
		else
		{
			cout << "IMPOSSIBLE\n";
		}
	}
}
