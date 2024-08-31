#include <bits/stdc++.h>

using namespace std;

map<string, int> ID;
vector<string>	 D;
int				 id(string const &s)
{
	auto [it, ins] = ID.try_emplace(s, (int)size(ID));
	if (ins)
		D.push_back(s);
	return it->second;
}

vector<vector<string>> tok()
{
	string				   ln;
	vector<vector<string>> ans;
	while (getline(cin, ln))
	{
		istringstream is(ln);
		ans.emplace_back();
		string s;
		while (is >> s)
		{
			if (s.back() == ':')
				s.pop_back();
			ans.back().push_back(move(s));
		}
	}
	return ans;
}

int					n;
vector<vector<int>> G;

void edfs(int v, string &ans)
{
	cout << D[v] << '\n';
	for (int w : G[v])
	{
		ans.push_back('0');
		edfs(w, ans);
		ans.push_back('1');
	}
}

void enc()
{
	auto				   T = tok();
	vector<pair<int, int>> E;
	for (auto const &row : T)
	{
		int mgr = id(row[0]);
		for (int i = 1; i < (int)size(row); i++)
			E.emplace_back(mgr, id(row[i]));
	}

	n = (int)size(D);
	G.resize(n);
	for (auto [u, v] : E)
		G[u].push_back(v);

	string ans;
	edfs(0, ans);
	cout << ans;
}

void ddfs(int &t, int &i)
{
	int v = t++;
	while (D.back()[i++] == '0')
	{
		G[v].push_back(t);
		ddfs(t, i);
	}
}
void dec()
{
	auto T = tok();
	n	   = (int)size(T) - 1;
	for (int i = 0; i <= n; i++)
		id(T[i][0]);
	G.resize(n);
	int t = 0, i = 0;
	ddfs(t, i);
	for (int v = 0; v < n; v++)
		if (!G[v].empty())
		{
			cout << D[v] << ':';
			for (int w : G[v])
				cout << ' ' << D[w];
			cout << '\n';
		}
}

int main()
{
	string cmd;
	getline(cin, cmd);
	if (cmd[0] == 'E')
		enc();
	else
		dec();
}
