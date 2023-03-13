#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int64_t>>> G;

struct dso
{
	int n;
	vector<int> P, R, M, E;
	vector<int64_t> S;
	dso(int n): n(n), P(n), R(n, 1), M(n, numeric_limits<int>::max() / 2), S(n), E(n)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
		{
			tie(x, P[x]) = make_pair(P[x], P[P[x]]);
		}
		return x;
	}
	bool onion(int x, int y, int c)
	{
		x = find(x);
		y = find(y);
		E[x]++;
		S[x] += c;
		M[x] = min(M[x], c);
		if (x == y) return false;
		if (R[x] < R[y])
			swap(x, y);
		P[y] = x;
		S[x] += S[y];
		M[x] = min(M[x], M[y]);
		E[x] += E[y];
		R[x] += R[y];
		return true;
	}
};

int main()
{
	int n, m;
	cin >> n >> m;

	dso D(n);

	int64_t s = 0;

	while (m--)
	{
		int u, v, c;
		cin >> u >> v >> c;
		u--;
		v--;
		D.onion(u, v, c);
		s += c;
	}

	if (D.R[D.find(0)] == n)
	{
		cout << s;
		return 0;
	}

	s = 0;
	for (int x = 0; x < n; x++)
	{
		if (D.P[x] != x)
			continue;
		s += D.S[x];
		cerr << x << ' ' << D.S[x] << ' ' << D.M[x] << endl;
		if (D.E[x] == D.R[x])
			s -= D.M[x];
	}
	cout << s;
}