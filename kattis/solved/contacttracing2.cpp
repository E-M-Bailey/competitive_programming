#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, k, c;
	cin >> n >> k >> c;
	vector<vector<int>> G(n);
	vector<int> L(n, -1);
	while (c--)
	{
		int a, b, d;
		cin >> a >> b >> d;
		a--;
		b--;
		d--;
		if (d > L[a]) G[a].clear();
		if (d > L[b]) G[b].clear();
		if (d >= L[a])
		{
			L[a] = d;
			G[a].push_back(b);
		}
		if (d >= L[b])
		{
			L[b] = d;
			G[b].push_back(a);
		}
	}

	unordered_set<int> I, J;
	for (int i = 0; i < n; i++)
		if (L[i] == 0)
			I.insert(i);
	for (int d = 0; d < k; d++)
	{
		for (int i : I)
			for (int j : G[i])
				if (L[j] == d + 1 || d == k - 1)
					J.insert(j);
		I.clear();
		J.swap(I);
	}
	cout << size(I) << '\n';
	vector<int> IV(begin(I), end(I));
	sort(begin(IV), end(IV));
	for (int j : IV)
		cout << j + 1 << '\n';
}