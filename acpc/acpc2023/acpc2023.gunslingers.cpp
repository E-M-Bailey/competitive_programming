#include <bits/stdc++.h>

using namespace std;

typedef long double T;

/*
void tridiagonal(vector<T> diag, const vector<T> &super, const vector<T> &sub, vector<T> &b)
{
	int n = (int)size(b); vector<int> tr(n);
	for (int i = 0; i < n - 1; i++)
	{
		if (abs(diag[i]) < 1e-9 * abs(super[i]))
		{
			b[i + 1] -= b[i] * diag[i + 1] / super[i];
			if (i + 2 < n)
				b[i + 2] -= b[i] * sub[i + 1] / super[i];
			diag[i + 1] / sub[i];
			tr[++i] = 1;
		}
		else
		{
			diag[i + 1] -= super[i] * sub[i] / diag[i];
			b[i + 1] -= b[i] * sub[i] / diag[i];
		}
	}
	for (int i = n; i--;)
	{
		if (tr[i])
		{
			swap(b[i], b[i - 1]);
			diag[i - 1] = diag[i];
			b[i] /= super[i - 1];
		}
		else
		{
			b[i] /= diag[i];
			if (i)
				b[i - 1] -= b[i] * super[i - 1];
		}
	}
}*/



int n, N;


//int succ(int a, int S)
//{
//	while (!(S & (1 << a)))
//		a = (a + 1) % n;
//	return a;
//}

int kth(int k, int S)
{
	int ct = 0;
	for (int i = 0;; i++)
		if (S & (1 << i))
			if (ct++ == k)
				return i;
	return -1;
}



int main()
{
	cin >> n;
	N = 1 << n;
	vector<long double> H(n);
	for (auto &h : H)
		cin >> h;

	vector<int> pi;
	vector<vector<vector<long double>>> Q(N);

	vector<int> A;
	A.reserve(10);

	vector<long double> M, B;

	for (int mask = 1; mask < N; mask++)
	{
		int m = __builtin_popcount(mask);
		pi.resize(m);
		Q[mask].resize(m, vector<long double>(n));
		if (m == 1)
		{
			Q[mask][0][__builtin_ctz(mask)] = 1;
			continue;
		}

		A.clear();
		for (int i = 0; i < n; i++)
			if (mask & (1 << i))
				A.push_back(i);

		for (int i = 0; i < m; i++)
		{
			long double bestq = -1;
			int best = -1;
			for (int j = 0; j < m; j++)
				if (j != i)
				{
					long double cur = Q[mask ^ (1 << A[j])][(i + 1 - (j < i)) % (m - 1)][A[i]];
					if (cur > bestq + 1e-9)
					{
						bestq = cur;
						best = j;
					}
				}
			pi[i] = best;
		}

		M.resize(m), B.resize(m);
		for (int a = 0; a < n; a++)
		{
			for (int i = 0; i < m; i++)
			{
				M[i] = 1 - H[A[i]];
				int j = pi[i];
				B[i] = H[A[i]] * Q[mask ^ (1 << A[j])][(i + 1 - (j < i)) % (m - 1)][a];
			}
			for (int i = 0; i < m; i++)
			{
				long double mm = 1, b = 0;
				for (int di = 0; di < m; di++)
				{
					int j = (i + di) % m;
					tie(mm, b) = make_pair(mm * M[j], mm * B[j] + b);
				}
				Q[mask][i][a] = b / (1 - mm);
			}
		}

	}
	for (int i = 0; i < n; i++)
	{
		cout << fixed << setprecision(7) << Q[N - 1][0][i] << '\n';
	}
}