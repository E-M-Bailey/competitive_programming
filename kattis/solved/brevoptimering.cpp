#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vector<int>					   M(n);
	vector<int>					   D(n);
	vector<vector<pair<int, int>>> G(n);

	for (int i = 0; i < n; i++)
	{
		int k;
		cin >> M[i] >> k;
		G[i].resize(k);
		for (auto &[j, w] : G[i])
		{
			cin >> j >> w;
			j--;
			D[j]++;
		}
	}

	vector<double> U(n);
	queue<int>	   Q;
	for (int i = 0; i < n; i++)
		if (D[i] == 0)
		{
			U[i] = M[i];
			Q.push(i);
		}

	while (!Q.empty())
	{
		int i = Q.front();
		Q.pop();
		U[i] = min(U[i], (double)M[i]);
		for (auto [j, w] : G[i])
		{
			U[j] += U[i] * w / 100;
			if (--D[j] == 0)
				Q.push(j);
		}
	}

	for (int i = 0; i < n; i++)
		if (U[i] >= M[i] - 1e-8)
			cout << i + 1 << ' ';
}
