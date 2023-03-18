#include <bits/stdc++.h>

using namespace std;
int t, n, m;

int main()
{
	cin >> t >> n >> m;
	vector<string> GR(n);
	for (auto& gr : GR)
		cin >> gr;
	vector<vector<int>> G(n * m);
	int s = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			char c = GR[i][j];
			if (i > 0 && (c == 'U' || c == '0'))
				G[(i - 1) * m + j].push_back(i * m + j);
			if (i < n - 1 && (c == 'D' || c == '0'))
				G[(i + 1) * m + j].push_back(i * m + j);
			if (j > 0 && (c == 'L' || c == '0'))
				G[i * m + (j - 1)].push_back(i * m + j);
			if (j < m - 1 && (c == 'R' || c == '0'))
				G[i * m + (j + 1)].push_back(i * m + j);
			if (c == 'S')
				s = i * m + j;
		}
	}
	vector<int> D(n * m, -1);
	D[s] = 0;
	queue<int> Q;
	Q.push(s);
	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int w : G[v])
		{
			if (D[w] >= 0)
				continue;
			D[w] = D[v] + 1;
			Q.push(w);
		}
	}
	int d = -1;
	for (int i = 0; i < n; i++)
	{
		if (D[i * m] >= 0 && (d < 0 || d > D[i * m]))
			d = D[i * m];
		if (D[i * m + (m - 1)] >= 0 && (d < 0 || d > D[i * m + (m - 1)]))
			d = D[i * m + (m - 1)];
	}
	for (int j = 0; j < m; j++)
	{
		if (D[j] >= 0 && (d < 0 || d > D[j]))
			d = D[j];
		if (D[(n - 1) * m + j] >= 0 && (d < 0 || d > D[(n - 1) * m + j]))
			d = D[(n - 1) * m + j];
	}
	if (d < 0 || d > t)
		cout << "NOT POSSIBLE\n";
	else
		cout << d << endl;
}