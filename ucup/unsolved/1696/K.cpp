#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> D[2];
vector<string>			   E[2];

int id(int i, string &s)
{
	auto [it, ins] = D[i].try_emplace(s, (int)size(D[i]));
	if (ins)
		E[i].push_back(move(s));
	return it->second;
}

int enc(string const &X)
{
	// if (X.back() == ',')
	// 	X.pop_back();
	return stoi(X.substr(3));
}

int main()
{
	string				   ln;
	vector<pair<int, int>> Ed;
	while (getline(cin, ln))
	{
		if (ln.empty())
			continue;
		istringstream is(ln);
		string		  U;
		is >> U;
		U.pop_back();
		int	   u = id(0, U);
		string V;
		while (is >> V)
		{
			if (V.back() == ',')
				V.pop_back();
			int v = id(1, V);
			Ed.emplace_back(v, u);
		}
	}

	int					n = (int)size(E[1]);
	vector<vector<int>> G(n);
	for (auto [v, u] : Ed)
		G[v].push_back(u);
	vector<int> I(n);
	iota(begin(I), end(I), 0);
	sort(begin(I),
		 end(I),
		 [](int i, int j)
		 {
			 return enc(E[1][i]) < enc(E[1][j]);
		 });
	for (int v : I)
	{
		cout << E[1][v];
		sort(begin(G[v]),
			 end(G[v]),
			 [](int i, int j)
			 {
				 return enc(E[0][i]) < enc(E[0][j]);
			 });
		bool fst = true;
		for (int u : G[v])
		{
			cout << (fst ? ':' : ',');
			fst = false;
			cout << ' ' << E[0][u];
		}
		cout << '\n';
	}
}