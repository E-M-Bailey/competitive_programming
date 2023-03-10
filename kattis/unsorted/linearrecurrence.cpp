#include <bits/stdc++.h>
using namespace std;

struct mul
{
	int64_t M;
	mul(int64_t M): M(M) {}
	vector<vector<int>> operator()(const vector<vector<int>>& A, const vector<vector<int>>& B) const
	{
		int a = size(A), b = size(A[0]), c = size(B[0]);
		vector<vector<int>> C(a, vector<int>(c));
		for (int i = 0; i < a; i++)
			for (int j = 0; j < b; j++)
				for (int k = 0; k < c; k++)
					C[i][k] = (C[i][k] + (int64_t)A[i][j] * B[j][k]) % M;
		return C;
	}
};

vector<vector<int>> eye(int n)
{
	vector<vector<int>> I(n, vector<int>(n));
	for (int i = 0; i < n; i++) I[i][i] = 1;
	return I;
}

vector<vector<int>> mpow(const vector<vector<int>>& A, int64_t t, const auto& op)
{
	if (t <= 1) return t ? A : eye(size(A));
	auto B = mpow(A, t / 2, op);
	return t % 2 ? op(op(B, B), A) : op(B, B);
}

int main()
{
	int n;
	cin >> n;
	vector<vector<int>> A(n + 1, vector<int>(n + 1));
	cin >> A[0][n];
	for (int i = 0; i < n; i++)
		cin >> A[0][i];
	for (int i = 1; i < n; i++)
		A[i][i - 1] = 1;
	A[n][n] = 1;
	vector<vector<int>> X(n + 1, vector<int>(1));
	for (int i = n - 1; i >= 0; i--)
		cin >> X[i][0];
	X[n][0] = 1;
	int q;
	cin >> q;
	while (q--)
	{
		int64_t t, m;
		cin >> t >> m;
		vector<vector<int>> B = A, Y = X;
		for (int i = 0; i <= n; i++)
		{
			B[0][i] = (B[0][i] % m + m) % m;
			Y[i][0] = (Y[i][0] % m + m) % m;
		}
		auto op = mul(m);
		cout << op(mpow(B, t, op), Y)[n - 1][0] << endl;
	}
}