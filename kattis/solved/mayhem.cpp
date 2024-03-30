#include <bits/extc++.h>

using namespace std;

struct dso
{
	vector<int> P, R;
	int			k;
	dso(int n) : P(n), R(n), k(n)
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
		if (R[x] < R[y])
			swap(x, y);
		P[y] = x;
		R[x] += R[x] == R[y];
		k--;
		return true;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	vector<string> G(n);
	int			   N = 0;
	for (auto &row : G)
	{
		cin >> row;
		N += (int)count(begin(row), end(row), 'x');
	}

	dso					D(N);
	int					ctr = 0;
	vector<vector<int>> R(n), C(m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (G[i][j] == 'x')
			{
				int cur = ctr++;
				R[i].push_back(cur);
				C[j].push_back(cur);
			}
	
	for (vector<int> const &RR : R)
		for (int i = 0; i < (int)size(RR) - 1; i++)
			D.onion(RR[i], RR[i + 1]);
	for (vector<int> const &CC : C)
		for (int i = 0; i < (int)size(CC) - 1; i++)
			D.onion(CC[i], CC[i + 1]);
	
	cout << N - D.k << '\n';
}