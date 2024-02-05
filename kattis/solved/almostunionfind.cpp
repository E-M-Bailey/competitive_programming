#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	while (cin >> n >> m)
	{
		vector<int64_t>				A(n);
		vector<list<int>>			S(n);
		vector<int>					I(n);
		vector<list<int>::iterator> IT(n);
		for (int i = 0; i < n; i++)
		{
			A[i]  = i;
			S[i]  = {i};
			I[i]  = i;
			IT[i] = S[i].begin();
		}

		while (m--)
		{
			int t, p, q;
			cin >> t;
			if (t == 1)
			{
				cin >> p >> q;
				int P = I[--p], Q = I[--q];
				if (P == Q)
					continue;
				if (S[P].size() < S[Q].size())
				{
					swap(P, Q);
					swap(p, q);
				}
				A[P] += A[Q];
				A[Q] = 0;
				for (int i : S[Q])
					I[i] = P;
				S[P].splice(S[P].end(), S[Q]);
			}
			else if (t == 2)
			{
				cin >> p >> q;
				int P = I[--p], Q = I[--q];
				if (P == Q)
					continue;
				A[Q] += p;
				A[P] -= p;
				I[p] = Q;
				S[Q].splice(S[Q].end(), S[P], IT[p]);
			}
			else
			{
				cin >> p;
				int P = I[--p];
				cout << S[P].size() << ' ' << A[P] + S[P].size() << '\n';
			}
		}
	}
}
