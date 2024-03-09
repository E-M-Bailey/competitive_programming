#include <bits/stdc++.h>

using namespace std;

typedef long double F;

// Assumes A full rank
void gj_elim(vector<valarray<F>> &A, vector<valarray<F>> &B)
{
	int n = (int)A.size(), m = (int)A[0].size();
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < n; j++)
			if (abs(A[j][i]) > abs(A[i][i]))
			{
				A[i].swap(A[j]);
				B[i].swap(B[j]);
			}
		F aii = A[i][i];
		A[i] /= aii;
		B[i] /= aii;
		for (int j = i + 1; j < n; j++)
		{
			F aji = A[j][i];
			A[j] -= A[i] * aji;
			B[j] -= B[i] * aji;
		}
	}
	for (int i = m - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			F aji = A[j][i];
			A[j] -= A[i] * aji;
			B[j] -= B[i] * aji;
		}
	}
}

pair<int, int> constexpr DIR[]
{
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};

int main()
{
	int l, w;
	cin >> l >> w;
	string dummy;
	getline(cin, dummy);

	vector<string> G(l);
	for (auto &row : G)
		getline(cin, row);

	int ie, je, id, jd;
	vector<pair<int, int>> S;
	vector<vector<int>> T(l, vector<int>(w, -1));
	for (int i = 0; i < l; i++)
		for (int j = 0; j < w; j++)
		{
			if (G[i][j] == ' ')
			{
				T[i][j] = (int)S.size();
				S.emplace_back(i, j);
			}
			else if (G[i][j] == 'E')
			{
				ie = i;
				je = j;
			}
			else if (G[i][j] == 'D')
			{
				id = i;
				jd = j;
			}
		}

	if (abs(id - ie) + abs(jd - je) == 1)
	{
		cout << fixed << setprecision(7) << (F)0;
		return 0;
	}

	int s = (int)S.size();

	vector<valarray<F>> A(s + 1, valarray<F>(s)), B(s + 1, valarray<F>(1));
	vector<vector<int>> H(s + 2);
	for (int i = 0; i < s; i++)
		A[i][i] = -1;
	for (int u = 0; u < s; u++)
	{
		auto [i, j] = S[u];
		for (auto [di, dj] : DIR)
		{
			int i2 = i + di, j2 = j + dj;
			if (i2 < 0 || i2 >= l || j2 < 0 || j2 >= w || T[i2][j2] < 0)
				continue;
			H[u].push_back(T[i2][j2]);
		}
		F wt = (F)1 / (F)H[u].size();
		for (int v : H[u])
			A[v][u] = wt;
	}
	{
		int u = s, i = ie, j = je;
		for (auto [di, dj] : DIR)
		{
			int i2 = i + di, j2 = j + dj;
			if (i2 < 0 || i2 >= l || j2 < 0 || j2 >= w || T[i2][j2] < 0)
				continue;
			H[u].push_back(T[i2][j2]);
			H[T[i2][j2]].push_back(u);
		}
	}
	{
		int u = s + 1, i = id, j = jd;
		for (auto [di, dj] : DIR)
		{
			int i2 = i + di, j2 = j + dj;
			if (i2 < 0 || i2 >= l || j2 < 0 || j2 >= w || T[i2][j2] < 0)
				continue;
			H[u].push_back(T[i2][j2]);
			H[T[i2][j2]].push_back(u);
		}
	}

	fill(begin(A[s]), end(A[s]), 1);
	B[s][0] = 1;
	gj_elim(A, B);

	vector<F> D(s + 2, 2);
	vector<bool> V(s + 2);
	priority_queue<pair<F, int>> Q;
	Q.emplace(0, s);
	while (!Q.empty())
	{
		auto [d, v] = Q.top();
		Q.pop();
		if (V[v])
			continue;
		V[v] = true;
		D[v] = d = -d;
		for (int u : H[v])
		{
			F wt = u >= s ? 0 : B[u][0];
			Q.emplace(-(d + wt), u);
		}
	}
	cout << fixed << setprecision(7) << D[s + 1];

}