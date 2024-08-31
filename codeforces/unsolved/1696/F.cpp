#include <bits/stdc++.h>

using namespace std;

int			n;
bitset<100> A[100][100];
bitset<100> V[100];
bitset<100> G[100];
int			D[100][100];

vector<pair<int, int>> CC;

int	 P[100], R[100];
void reset()
{
	fill_n(R, n, 0);
	iota(P, P + n, 0);
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
	return true;
}

void dfs(int u, int v)
{
	CC.emplace_back(u, v);
	V[u][v] = V[v][u] = true;
	for (int w = 0; w < n; w++)
		if (!V[v][w] && A[v][u][w])
			dfs(v, w);
}

bool tree()
{
	if ((int)size(CC) != n - 1)
		return false;
	reset();
	for (auto [u, v] : CC)
		if (!onion(u, v))
			return false;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			D[i][j] = D[j][i] = n;
	for (auto [u, v] : CC)
		D[u][v] = D[v][u] = 1;
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (A[i][j][k] ^ (D[i][j] == D[i][k]))
					return false;
	return true;
}

int main()
{
	for (int i = 0; i < 100; i++)
	{
		V[i][i] = true;
		for (int j = 0; j < 100; j++)
			A[i][j][j] = true;
	}

	cin.tie(0)->sync_with_stdio(0);

	int tc;
	cin >> tc;
	while (tc--)
	{
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				for (int k = 0; k < n; k++)
				{
					char c;
					cin >> c;
					A[k][i][j] = A[k][j][i] = c == '1';
				}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
				V[i][j] = V[j][i] = false;

		bool found = false;

		for (int i = 0; !found && i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j && !V[i][j])
				{
					CC.clear();
					for (int k = j; k < n; k++)
						if (A[i][j][k] && !V[i][k])
							dfs(i, k);
					if (tree())
					{
						found = true;
						cout << "Yes\n";
						for (auto [u, v] : CC)
							cout << u + 1 << ' ' << v + 1 << '\n';
						break;
					}
				}
		if (!found)
			cout << "No\n";
	}
}
