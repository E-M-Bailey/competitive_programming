#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	// cin >> tc;
	while (tc--)
		go();
}

constexpr int M = 1000000007;

constexpr int I[5]{0, 1, 3, 2, 4};

void go()
{
	int n, m;
	cin >> n >> m;
	int					ct = 1;
	vector<vector<int>> A(n, vector<int>(m));
	for (auto &AA : A)
		for (int &a : AA)
		{
			char c;
			cin >> c;
			a = c - 'a';
		}

	int dim = 0;
	for (int i = 0; i < m; i++)
	{
		int p = -1;
		for (int j = dim; j < n; j++)
			if (A[j][i])
			{
				p = j;
				break;
			}
		if (p < 0)
			continue;
		A[p].swap(A[dim]);
		for (int k = m; k-- > i;)
			A[dim][k] = A[dim][k] * I[A[dim][i]] % 5;
		for (int j = dim + 1; j < n; j++)
			if (A[j][i])
				for (int k = m; k-- > i;)
					A[j][k] = (A[j][k] * I[A[j][i]] + 5 - A[dim][k]) % 5;
		dim++;
	}
	for (int i = dim; i < n; i++)
		ct = int(ct * 5ll % M);
	A.resize(dim);

	int q;
	cin >> q;
	while (q--)
	{
		vector<int> B(m);
		for (int &b : B)
		{
			char c;
			cin >> c;
			b = c - 'a';
		}

		int p = 0;
		for (int i = 0; i < dim; i++)
		{
			while (A[i][p] == 0)
				p++;
			for (int k = m; k-- > p;)
				B[k] = (B[k] + 25 - B[p] * A[i][k]) % 5;
		}
		cout << (all_of(begin(B), end(B), [](int b){return b == 0;}) ? ct : 0) << '\n';
	}
}
