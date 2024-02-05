#include <bits/stdc++.h>

using namespace std;

string		 ln;
vector<bool> rd(int k)
{
	vector<bool> ans(k);
	getline(cin, ln);
	istringstream in(move(ln));
	for (int i; in >> i;)
		ans[i] = true;
	return ans;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, m, k;
		cin >> n >> m >> k;
		getline(cin, ln);
		vector<vector<bool>> nd(n), cr(n);
		for (int i = 0; i < n; i++)
		{
			nd[i] = rd(k);
			cr[i] = rd(k);
		}
		vector<int>			V(m);
		vector<vector<int>> G(n);
		for (int &v : V)
		{
			int u;
			cin >> u >> v;
			G[v].push_back(u);
		}

		vector<int> S;
		for (int i = 0; i < k; i++)
		{
			for (int v = 0; v < n; v++)
				if (nd[v][i])
					S.push_back(v);
			while (!S.empty())
			{
				int v = S.back();
				S.pop_back();
				for (int u : G[v])
					if (!nd[u][i] && !cr[u][i])
					{
						nd[u][i] = true;
						S.push_back(u);
					}
			}
		}
		for (int v : V)
		{
			for (int i = 0; i < k; i++)
				if (nd[v][i])
					cout << i << ' ';
			cout << '\n';
		}
	}
}
