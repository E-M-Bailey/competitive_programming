#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, m;
	cin >> n >> m;

	unordered_set<int>	   A, B;
	vector<vector<int>>	   G(n);
	queue<pair<int, bool>> Q;
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--;
		b--;
		if (c == 0)
		{
			Q.emplace(a, false);
			Q.emplace(b, false);
		}
		else if (c == 2)
		{
			Q.emplace(a, true);
			Q.emplace(b, true);
		}
		else
		{
			G[a].push_back(b);
			G[b].push_back(a);
		}
	}
	vector<bool> V(n, false);
	while (!Q.empty())
	{
		auto [i, l] = Q.front();
		Q.pop();
		(l ? B : A).insert(i);
		if (A.find(i) != end(A) && B.find(i) != end(B))
		{
			cout << "impossible";
			return 0;
		}
		if (V[i])
			continue;
		V[i] = true;
		for (int j : G[i])
			Q.emplace(j, !l);
	}

	unordered_set<int> C, D;
	for (int i = 0; i < n; i++)
	{
		if (V[i])
			continue;
		C.insert(i);
		Q.emplace(i, false);
		while (!Q.empty())
		{
			auto [v, l] = Q.front();
			Q.pop();
			(l ? D : C).insert(v);
			if (C.find(v) != end(C) && D.find(v) != end(D))
			{
				cout << "impossible";
				return 0;
			}
			if (V[v])
				continue;
			V[v] = true;
			for (int w : G[v])
				Q.emplace(w, !l);
		}
		if (C.size() >= D.size())
		{
			for (int c : C)
				A.insert(c);
			for (int d : D)
				B.insert(d);
		}
		else
		{
			for (int d : D)
				A.insert(d);
			for (int c : C)
				B.insert(c);
		}
		C.clear();
		D.clear();
	}
	cout << B.size();
}
