#include <bits/stdc++.h>
using namespace std;

int main()
{
	int p;
	cin >> p;
	while (p--)
	{
		int n;
		cin >> n;
		cout << n;
		cin >> n;

		vector<int> rd(n), gr(n);
		for (int& r : rd)
			cin >> r;
		for (int& g : gr)
			cin >> g;

		vector<vector<int>> G(n * n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				int a = i * n + j;
				int br = rd[i] * n + rd[j];
				int bg = gr[i] * n + gr[j];
				G[br].push_back(a);
				G[bg].push_back(a);
			}

		queue<int> Q;
		vector<bool> V(n * n);
		for (int i = 0; i < n; i++)
		{
			Q.push(i * n + i);
			V[i * n + i] = true;
		}

		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for (int w : G[v])
			{
				if (V[w])
					continue;
				V[w] = true;
				Q.push(w);
			}
		}

		bool ans = accumulate(V.begin(), V.end(), true, logical_and());
		cout << (ans ? " YES\n" : " NO\n");
	}
}