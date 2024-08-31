#include <bits/stdc++.h>

using namespace std;

int n, r;
vector<vector<int>> C;

int dfs(int v, int tgt)
{
	int k = (int)size(C[v]);
	int up = k - tgt;
	for (int w : C[v])
		up += dfs(w, tgt);
	return max(0, up);
}

int main()
{
	cin >> n;
	C.resize(n);
	for (int i = 0; i < n; i++)
	{
		int p;
		cin >> p;
		if (p == 0)
			r = i;
		else
			C[p - 1].push_back(i);
	}

	int lo = -1, hi = 0;
	for (auto const &CC : C)
		hi = max(hi, (int)size(CC));
	
	while (hi - lo > 1)
	{
		int mid = (lo + hi + 1) / 2;
		if (dfs(r, mid))
			lo = mid;
		else
			hi = mid;
	}
	cout << lo + 1;
}