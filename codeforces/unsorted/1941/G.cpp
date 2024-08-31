#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	while (t--)
		go();
}

void go()
{
	int n, m;
	cin >> n >> m;
	vector<int>					 C;
	vector<tuple<int, int, int>> E(m);
	for (auto &[u, v, c] : E)
	{
		cin >> u >> v >> c;
		u--;
		v--;
		C.push_back(c);
	}
	int b, e;
	cin >> b >> e;
	b--;
	e--;

	sort(ALL(C));
	C.erase(unique(ALL(C)), end(C));
	int k = (int)size(C);

	vector<vector<int>> G(n + k);
	for (auto [u, v, c] : E)
	{
		c = int(lower_bound(ALL(C), c) - begin(C));
		G[u].push_back(c + n);
		G[v].push_back(c + n);
		G[c + n].push_back(u);
		G[c + n].push_back(v);
	}

	vector<bool> V(n + k, false);
	V[b] = true;
	queue<int> Q;
	Q.push(b);
	for (int d = 0;; d++)
	{
		for (int sz = (int)size(Q); sz--;)
		{
			int v = Q.front();
			Q.pop();
			if (v == e)
			{
				cout << d / 2 << '\n';
				return;
			}
			for (int w : G[v])
				if (!V[w])
				{
					Q.push(w);
					V[w] = true;
				}
		}
	}
}
