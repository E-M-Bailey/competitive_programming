#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<unordered_multiset<int>> G(n);
	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		G[a].insert(b);
		G[b].insert(a);
	}


	vector<int> D1;
	for (int v = 0; v < n; v++)
		if (G[v].size() == 1)
			D1.push_back(v);

	while (!D1.empty())
	{
		int v = D1.back(), w = *begin(G[v]);
		D1.pop_back();
		cout << v + 1 << ' ' << w + 1 << '\n';
		G[v].erase(G[v].find(w));
		G[w].erase(G[w].find(v));
		if (G[w].size() == 1)
			D1.push_back(w);
	}

	for (int i = 0; i < n; i++)
		if (!G[i].empty())
			for (int v = i, w = *begin(G[v]);; v = w, w = *begin(G[v]))
			{
				cout << v + 1 << ' ' << w + 1 << '\n';
				G[v].erase(G[v].find(w));
				G[w].erase(G[w].find(v));
				if (G[w].empty())
					break;
			}
}