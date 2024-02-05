#include <bits/stdc++.h>

using namespace std;

int			n, k;
vector<int> G[100001];

vector<int> dfs(int x, int y)
{
	vector<int> A(k);

	iota(begin(A), end(A), 1);

	for (int w : G[y])
	{
		if (w == x)
			continue;
		vector<int> R = dfs(y, w);
		int			a = INT_MAX, j = -1, b = INT_MAX;
		for (int i = k; i--;)
		{
			if (R[i] < b)
				b = R[i];
			if (R[i] < a)
			{
				swap(a, b);
				j = i;
			}
		}
		for (int i = k; i--;)
			A[i] += a;
		A[j] += b - a;
	}
	return A;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> k;

	for (int i = 1; i < n; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	vector<int> A = dfs(1, 1);
	cout << (k == 1 && n > 1 ? -1 : *min_element(begin(A), end(A)));
}
