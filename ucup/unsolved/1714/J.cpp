#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> S, P;
	dso(int N) : S(N, 1), P(N)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = pair{P[x], P[P[x]]};
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (S[x] < S[y])
			swap(x, y);
		P[y] = x;
		S[x] += S[y];
		return true;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<int> P(n);
		vector<int> Q(n);
		for (int &p : P)
		{
			cin >> p;
			p--;
		}
		for (int i = 0; i < n; i++)
			Q[P[i]] = i;
		vector<vector<int>> C;
		vector<bool>		V(n, false);
		for (int i = 0; i < n; i++)
		{
			if (V[i])
				continue;
			C.emplace_back();
			int j = i;
			do
			{
				C.back().push_back(j);
				V[j] = true;
				j	 = P[j];
			}
			while (j != i);
		}

		if (size(C) >= 2)
		{
			cout << n << '\n' << size(C[0]) << '\n';
			for (int a : C[0])
				cout << Q[a] + 1 << ' ';
		}
		else
		{
			dso D(n);
			for (int i = 0; i < n - 2; i++)
				D.onion(i, P[i]);
			int x = D.find(0);
			cout << n - 2 << '\n' << D.S[x] << '\n';
			for (int a = 0; a < n; a++)
				if (D.find(a) == x)
					cout << Q[a] + 1 << ' ';
		}
		cout << '\n';
	}
}
