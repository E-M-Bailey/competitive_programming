#include <bits/stdc++.h>

using namespace std;

int constexpr MOD = 1e9 + 7;


int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		vector<array<int, 50>> A(50), B(50), M(50), N(50);
		vector<bitset<50>> BA(50), BB(50), BM(50), BN(50);
		int n, K;
		cin >> n >> K;
		for (int i = 1; i < 50; i++)
		{
			A[i][i - 1] = 1;
			BA[i][i - 1] = true;
		}
		while (K--)
		{
			int l;
			cin >> l;
			A[0][l - 1]++;
			BA[0][l - 1] = true;
		}
		//cerr << endl;

		for (int i = 0; i < 50; i++)
		{
			M[i][i] = 1;
			BM[i][i] = true;
		}

		for (; n; n /= 2)
		{
			if (n % 2)
			{
				for (int i = 0; i < 50; i++)
					for (int j = 0; j < 50; j++)
					{
						N[i][j] = 0;
						BN[i][j] = false;
						for (int k = 0; k < 50; k++)
						{
							N[i][j] = int((N[i][j] + (int64_t)A[i][k] * M[k][j]) % MOD);
							BN[i][j] = BN[i][j] | (BA[i][k] & BM[k][j]);
						}
					}
				N.swap(M);
				BN.swap(BM);
			}
			for (int i = 0; i < 50; i++)
				for (int j = 0; j < 50; j++)
				{
					B[i][j] = 0;
					BB[i][j] = false;
					for (int k = 0; k < 50; k++)
					{
						B[i][j] = int((B[i][j] + (int64_t)A[i][k] * A[k][j]) % MOD);
						BB[i][j] = BB[i][j] | (BA[i][k] & BA[k][j]);
					}
				}
			A.swap(B);
			BA.swap(BB);
		}

		int ans = M[0][0];
		if (BM[0][0])
			cout << ans << '\n';
		else
			cout << "IMPOSSIBLE\n";
	}
}