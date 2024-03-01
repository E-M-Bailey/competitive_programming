#include <bits/stdc++.h>

using namespace std;

char opp[256];
bool cl[256];

vector<vector<int>> G;
vector<int>			S{-1};
string				str;

int dfs(int u, int v)
{
	int c = str[v];
	if (cl[c] && S.back() != opp[c])
		return 0;

	if (cl[c])
		S.pop_back();
	else
		S.push_back(c);

	int ans = size(S) == 1;
	for (int w : G[v])
		if (w != u)
			ans += dfs(v, w);

	if (cl[c])
		S.push_back(opp[c]);
	else
		S.pop_back();

	return ans;
}

int main()
{
	opp[(int)'('] = ')';
	opp[(int)')'] = '(';
	opp[(int)'{'] = '}';
	opp[(int)'}'] = '{';
	opp[(int)'['] = ']';
	opp[(int)']'] = '[';
	cl[(int)')'] = cl[(int)'}'] = cl[(int)']'] = true;

	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n >> str;
	G.resize(n);
	S.reserve(n);

	for (int i = 0; i < n - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int ans = 0;
	for (int i = 0; i < n; i++)
		ans += dfs(i, i);

	cout << ans;
}
