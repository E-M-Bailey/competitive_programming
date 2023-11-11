#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n, m, t;
		cin >> n >> m >> t;
		int s, g, h;
		cin >> s >> g >> h;
		s--;
		g--;
		h--;
		vector<vector<pair<int, int>>> G(n);
		while (m--)
		{
			int a, b, d;
			cin >> a >> b >> d;
			a--;
			b--;
			G[a].emplace_back(b, d);
			G[b].emplace_back(a, d);
		}
		vector<int> X(t);
		for (int &x : X)
			cin >> x;

		vector<int> D(n, INT_MAX);
		vector<bool> V(n);
		D[s] = 0;
		priority_queue<pair<int, int>> PQ;
		PQ.emplace(0, s);
		while (!PQ.empty())
		{
			int v = PQ.top().second;
			PQ.pop();
			if (V[v])
				continue;
			V[v] = true;
			for (auto [w, wt] : G[v])
				if (D[w] > D[v] + wt)
				{
					D[w] = D[v] + wt;
					PQ.emplace(-D[w], w);
				}
		}

		if (D[h] < D[g])
			swap(g, h);

		V.assign(n, false);
		queue<int> Q;
		Q.push(h);
		V[h] = true;
		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for (auto [w, wt] : G[v])
				if (!V[w] && D[w] == D[v] + wt)
				{
					V[w] = true;
					Q.push(w);
				}
		}
		sort(begin(X), end(X));
		for (int x : X)
			if (V[x - 1])
				cout << x << ' ';
		cout << '\n';
	}
}