#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, R;
	int make_set()
	{
		int ans = (int)P.size();
		P.push_back(ans);
		R.push_back(0);
		return ans;
	}

	int find(int x)
	{
		if (x < 0)
			return -1;
		while (x != P[x])
			tie(x, P[x]) = make_pair(P[x], P[P[x]]);
		return x;
	}

	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x < 0 || y < 0 || x == y)
			return false;
		if (R[x] < R[y])
			swap(x, y);
		P[y] = x;
		R[x] += R[x] == R[y];
		return true;
	}

	bool conn(int x, int y)
	{
		x = find(x);
		y = find(y);
		return x >= 0 && x == y;
	}
} D;

int const BIG = 1'000'000'100;

int m, n, q;
vector<int> X, Y;
unordered_set<int> SX{ -BIG, BIG }, SY = SX;
vector<array<int, 4>> C;

// a b c d
// c d a b
// b a
// d c 
// 0 1
// 2 3
// 4 5
// 6 7

int const TWO[]{ 0, 1, 2, 3, 1, 0, 3, 2 };

int cc_at(int x, int y)
{
	if (x <= X.front() || x >= X.back() || y <= Y.front() || y >= Y.back() || SX.find(x) != SX.end() || SY.find(y) != SY.end())
		return -1;
	int i = upper_bound(begin(X), end(X), x) - begin(X) - 1;
	int j = upper_bound(begin(Y), end(Y), y) - begin(Y) - 1;
	int dx = X[i + 1] - X[i] - 1, dy = Y[j + 1] - Y[j] - 1;
	x -= X[i] + 1;
	y -= Y[j] + 1;
	int idx = i * n + j;
	if (dx == 0 || dy == 0)
		exit(-1);
	if (dx == 1 || dy == 1)
		return C[idx][(x + y) % 2];
	else if (dx == 2)
		return C[idx][TWO[(x + 2 * y) % 8]];
	else if (dy == 2)
		return C[idx][TWO[(2 * x + y) % 8]];
	else
		return C[idx][0];
}

pair<int, int> const DIR[8]
{
	{1, 2},
	{2, 1},
	{1, -2},
	{2, -1},
	{-1, 2},
	{-2, 1},
	{-1, -2},
	{-2, -1}
};
bool isol(int x, int y)
{
	for (auto [dx, dy] : DIR)
		if (SX.find(x + dx) == SX.end() && SY.find(y + dy) == SY.end())
			return false;
	return true;
}

int main()
{
	cin >> n >> q;

	while (n--)
	{
		int rx, ry;
		cin >> rx >> ry;
		SX.insert(rx);
		SY.insert(ry);
	}
	X.assign(begin(SX), end(SX));
	Y.assign(begin(SY), end(SY));
	sort(begin(X), end(X));
	sort(begin(Y), end(Y));
	m = (int)X.size() - 1;
	n = (int)Y.size() - 1;
	C.resize(m * n);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			int dx = X[i + 1] - X[i] - 1, dy = Y[j + 1] - Y[j] - 1;
			int idx = i * n + j;
			if (dx == 0 || dy == 0)
				C[idx] = { -1, -1, -1, -1 };
			else if (dx == 1 || dy == 1)
				C[idx] = { D.make_set(), D.make_set(), -1, -1 };
			else if (dx == 2 || dy == 2)
				C[idx] = { D.make_set(), D.make_set(), D.make_set(), D.make_set() };
			else
				C[idx] = { D.make_set(), -1, -1, -1 };
		}

	for (int i = 0; i < m; i++)
		for (int j = 1; j < n; j++)
			for (int x = X[i] + 1; x <= X[i] + 6; x++)
			{
				int c = cc_at(x, Y[j] - 1);
				D.onion(c, cc_at(x - 1, Y[j] + 1));
				D.onion(c, cc_at(x + 1, Y[j] + 1));
			}
	for (int i = 1; i < m; i++)
		for (int j = 0; j < n; j++)
			for (int y = Y[j] + 1; y <= Y[j] + 6; y++)
			{
				int c = cc_at(X[i] - 1, y);
				D.onion(c, cc_at(X[i] + 1, y - 1));
				D.onion(c, cc_at(X[i] + 1, y + 1));
			}

	while (q--)
	{
		int sx, sy, tx, ty;
		cin >> sx >> sy >> tx >> ty;
		if (isol(sx, sy))
		{
			// cerr << "s isol" << endl;
			cout << "0\n";
		}
		else if (isol(tx, ty))
		{
			// cerr << "t isol" << endl;
			cout << "0\n";
		}
		else if (!D.conn(cc_at(sx, sy), cc_at(tx, ty)))
		{
			// cerr << "disconnected (" << D.find(cc_at(sx, sy)) << ' ' << D.find(cc_at(tx, ty)) << ')' << endl;
			cout << "0\n";
		}
		else
		{
			// cerr << "connected (" << D.find(cc_at(sx, sy)) << ')' << endl;
			cout << "1\n";
		}


	}
}
