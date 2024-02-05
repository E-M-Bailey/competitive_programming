#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1000000009;

typedef vector<vector<int64_t>> mat;

mat matmul(mat const &A, mat const &B)
{
	mat C(A.size(), vector<int64_t>(B[0].size()));
	for (int i = 0; i < (int)A.size(); i++)
		for (int j = 0; j < (int)B[0].size(); j++)
		{
			int64_t sum = 0;
			for (int k = 0; k < (int)B.size(); k++)
				sum = (sum + A[i][k] * B[k][j]) % MOD;
			C[i][j] = sum;
		}
	return C;
}

mat matpow(mat A, int64_t b)
{
	mat C(A.size(), vector<int64_t>(A.size()));
	for (int i = 0; i < (int)A.size(); i++)
		C[i][i] = 1;
	for (; b; b /= 2, A = matmul(A, A))
		if (b % 2)
			C = matmul(A, C);
	return C;
}



int main()
{
	int64_t a, b, c, d, e;
	cin >> a >> b >> c >> d >> e;

	vector<int64_t> F(20);
	F[0] = 1;
	vector<pair<int64_t, int>> X{ pair{ a, 4 }, pair{ b, 6 }, pair{ c, 8 }, pair{ d, 12 }, pair{ e, 20 } };
	for (auto [f, n] : X)
	{
		vector<vector<int64_t>> A(n, vector<int64_t>(n));
		vector<vector<int64_t>> B(n, vector<int64_t>(1));
		for (int i = 0; i < n; i++)
		{
			B[i][0] = F[i];
			for (int j = 0; j <= i; j++)
				A[i][j] = 1;
		}
		B = matmul(matpow(A, f), B);
		for (int i = 0; i < n; i++)
			F[i] = B[i][0];
		// for (auto ff : F)
		// 	cerr << ff << ' ';
		// cerr << endl;
	}
	cout << accumulate(begin(F), end(F), 0ll) % MOD;
}
