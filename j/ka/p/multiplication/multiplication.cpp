#include <bits/stdc++.h>

using namespace std;

int main()
{
	string A, B;
	while (cin >> A >> B, A != "0")
	{
		int m = (int)A.size(), n = (int)B.size();
		int M = 5 + 4 * m, N = 5 + 4 * n;
		vector<string> G(N, string(M, ' '));
		G[0][0] = G[0][M - 1] = G[N - 1][0] = G[N - 1][M - 1] = '+';

		for (int J = 1; J < M - 1; J++)
			G[0][J] = G[N - 1][J] = '-';

		for (int I = 1; I < N - 1; I++)
			G[I][0] = G[I][M - 1] = '|';

		for (int I = 2; I < N; I += 4)
			for (int J = 2; J < M - 2; J++)
				G[I][J] = '-';

		for (int I = 2; I < N - 2; I++)
			for (int J = 2; J < M; J += 4)
				G[I][J] = '|';

		for (int I = 2; I < N; I += 4)
			for (int J = 2; J < M; J += 4)
				G[I][J] = '+';

		for (int j = 0, J = 4; j < m; j++, J += 4)
			G[1][J] = A[j];

		for (int i = 0, I = 4; i < n; i++, I += 4)
			G[I][M - 2] = B[i];

		for (int i = 0, I = 2; i < n; i++, I += 4)
			for (int j = 0, J = 2; j < m; j++, J += 4)
			{
				int a = A[j] - '0', b = B[i] - '0';
				G[I + 1][J + 3] = G[I + 2][J + 2] = G[I + 3][J + 1] = '/';
				G[I + 1][J + 1] = char(a * b / 10 + '0');
				G[I + 3][J + 3] = char(a * b % 10 + '0');
			}

		string C = to_string(atoi(A.c_str()) * atoi(B.c_str()));
		int l = (int)C.size();
		for (int k = 0, I = (m + n == l ? 2 : 6); k < l - m; k++, I += 4)
		{
			G[I + 3][1] = C[k];
			G[I + 5][1] = '/';
		}
		for (int k = l - m, J = 2; k < l; k++, J += 4)
		{
			G[N - 2][J + 1] = C[k];
			G[N - 2][J + 3] = '/';
		}
		G[N - 2][M - 4] = ' ';

		for (auto const &row : G)
			cout << row << '\n';
	}
}