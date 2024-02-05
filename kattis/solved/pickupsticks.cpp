#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n);
	vector<int>			ID(n);
	while (m--)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		G[a].push_back(b);
		ID[b]++;
	}
	vector<int> S;
	S.reserve(n);
	for (int i = 0; i < n; i++)
		if (ID[i] == 0)
			S.push_back(i);

	vector<int> ans;
	ans.reserve(n);
	while (!S.empty())
	{
		int v = S.back();
		S.pop_back();
		ans.push_back(v);
		for (int w : G[v])
			if (--ID[w] == 0)
				S.push_back(w);
	}
	if ((int)ans.size() < n)
		cout << "IMPOSSIBLE";
	else
		for (int a : ans)
			cout << a + 1 << '\n';
}
