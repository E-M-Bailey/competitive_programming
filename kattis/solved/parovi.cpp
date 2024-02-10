#include <bits/stdc++.h>

using namespace std;

vector<int> in()
{
	static string x;
	cin >> x;
	int			n = (int)x.size();
	vector<int> ans(n);
	for (int i = 0; i < n; i++)
		ans[i] = x[n - 1 - i] - '0';
	return ans;
}

int64_t constexpr MOD = 1000000007;
int e[10][10]{}, E[10][10]{}, f[11][10]{}, F[11][10]{}, g[11][11]{}, G[11][11]{};

int64_t solve(vector<int> const &X, vector<int> const &Y)
{
	int		n = (int)size(X);
	int64_t a = 0, b = 0, c = 0, d = 0, A = 1, B = 0, C = 0, D = 0;
	for (int i = 0; i < n; i++)
	{
		int x = X[i], y = Y[i];
		d = (G[x][y] * a + g[x][y] * A + F[y][x] * b + f[y][x] * B + F[x][y] * c + f[x][y] * C + E[x][y] * d + e[x][y] * D) % MOD;
		D = (G[x][y] * A + F[y][x] * B + F[x][y] * C + E[x][y] * D) % MOD;
		c = (G[10][y] * a + g[10][y] * A + F[10][y] * c + f[10][y] * C) % MOD;
		C = (G[10][y] * A + F[10][y] * C) % MOD;
		b = (G[10][x] * a + g[10][x] * A + F[10][x] * b + f[10][x] * B) % MOD;
		B = (G[10][x] * A + F[10][x] * B) % MOD;
		a = (G[10][10] * a + g[10][10] * A) % MOD;
		A = (G[10][10] * A) % MOD;
	}
	return d;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			e[i][j] = abs(i - j);
			E[i][j] = 1;
		}
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 10; j++)
			for (int k = 0; k < i; k++)
			{
				f[i][j] += e[k][j];
				F[i][j] += E[k][j];
			}
	for (int i = 0; i < 11; i++)
		for (int j = 0; j < 11; j++)
			for (int k = 0; k < j; k++)
			{
				g[i][j] += f[i][k];
				G[i][j] += F[i][k];
			}

	auto X = in(), Y = in();
	Y[0]++;
	Y.push_back(0);
	for (int i = 0; Y[i] == 10; i++)
	{
		Y[i] = 0;
		Y[i + 1]++;
	}
	if (Y.back() == 0)
		Y.pop_back();
	int n = (int)max(size(Y), size(X));
	X.resize(n);
	Y.resize(n);
	cout << (solve(Y, Y) + 2 * (MOD - solve(X, Y)) + solve(X, X)) % MOD;
}
