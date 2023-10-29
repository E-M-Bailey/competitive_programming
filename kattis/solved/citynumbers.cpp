#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma")
#ifndef GODBOLT
#pragma GCC target("tune=native")
#endif

using namespace std;

typedef vector<int> vi;

int n, k;
vi G[100001];

vi dfs(int x, int y)
{
	vi A(k);
	
	iota(begin(A), end(A), 1);

	for (int w : G[y])
	{
		if (w == x)
			continue;
		vi R = dfs(y, w);
		int a = INT_MAX, j = -1, b = INT_MAX;
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

	vi A = dfs(1, 1);
	cout << (k == 1 && n > 1 ? -1 : *min_element(begin(A), end(A)));
}