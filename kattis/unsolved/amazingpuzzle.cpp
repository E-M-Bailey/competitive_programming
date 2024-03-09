#include <bits/stdc++.h>

using namespace std;

pair<int, int> const DIR[4]
{
	pair<int, int>{1, 0},
	pair<int, int>{0, 1},
	pair<int, int>{-1, 0},
	pair<int, int>{0, -1}
};

int L[256];

int n, m;

int idx(int i, int j, int d)
{
	return (i * m + j) * 4 + d;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	
	L[(int)'N'] = 0;
	L[(int)'E'] = 1;
	L[(int)'S'] = 2;
	L[(int)'W'] = 3;

	int e;
	cin >> m >> n >> e;
	e--;
	int N = 4 * m * n + 1;
	vector<vector<bool>> H(n - 1, vector<bool>(m)), V(n, vector<bool>(m - 1));
	int is, js;
	{
		int ia, ja, ib, jb;
		char da, db;
		cin >> ja >> ia >> da >> jb >> ib >> db;
		is = idx(ia - 1, ja - 1, L[(int)da]);
		js = idx(ib - 1, jb - 1, L[(int)db]);
		int k, c, r;
		cin >> k;
		while (k--)
		{
			cin >> c >> r;
			H[r - 1][c - 1] = true;
		}
		cin >> k;
		while (k--)
		{
			cin >> c >> r;
			V[r - 1][c - 1] = true;
		}
	}

	vector<vector<int>> A(N), B(N), C(N);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			int v = idx(i, j, 0);
			for (int d = 0; d < 4; d++)
			{
				int d2 = (d + 1) % 4;
				B[v + d].push_back(v + d2);
				C[v + d2].push_back(v + d);
			}
			A[v].push_back(v + (i < n - 1 && !H[i][j]) * m * 4);
			A[v + 1].push_back(v + 1 + (j < m - 1 && !V[i][j]) * 4);
			A[v + 2].push_back(v + 2 - (i > 0 && !H[i - 1][j]) * m * 4);
			A[v + 3].push_back(v + 3 - (j > 0 && !V[i][j - 1]) * 4);
		}

	A[idx(0, e, 2)].push_back(N - 1);
	A[N - 1].push_back(N - 1);
	B[N - 1].push_back(N - 1);
	C[N - 1].push_back(N - 1);

	vector<vector<pair<int, int>>> D(N, vector<pair<int, int>>(N, { INT_MAX, INT_MAX }));
	D[is][js] = { 0, 0 };
	priority_queue<tuple<int, int, int, int>> Q;
	Q.emplace(0, 0, is, js);
	while (!Q.empty())
	{
		auto [da, db, i, j] = Q.top();
		da = -da;
		db = -db;
		pair<int, int> d(da, db);
		Q.pop();
		if (D[i][j] != d || i / 4 == j / 4)
			continue;
		for (int wi : A[i])
			for (int wj : A[j])
			{
				bool ba = wi == i && i != N - 1;
				bool bb = wj == j && j != N - 1;
				pair<int, int> d2(da + 1, db + ba + bb);
				if (d2 < D[wi][wj])
				{
					D[wi][wj] = d2;
					Q.emplace(-(da + 1), -(db + ba + bb), wi, wj);
				}
			}
		for (int wi : B[i])
			for (int wj : B[j])
			{
				pair<int, int> d2(da, db);
				if (d2 < D[wi][wj])
				{
					D[wi][wj] = d2;
					Q.emplace(-da, -db, wi, wj);
				}
			}
		for (int wi : C[i])
			for (int wj : C[j])
			{
				pair<int, int> d2(da, db);
				if (d2 < D[wi][wj])
				{
					D[wi][wj] = d2;
					Q.emplace(-da, -db, wi, wj);
				}
			}
	}
	auto [da, db] = D[N - 1][N - 1];
	cout << da << ' ' << db;
}