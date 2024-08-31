#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	// if (argc > 1)
	// {
	// 	ignore = freopen(argv[1], "r", stdin);
	// 	ignore = freopen(argv[2], "w", stdout);
	// }
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n;
	cin >> n;

	vector<bool>		   V(n, false);
	vector<int>			   D(n, 0);
	vector<pair<int, int>> E;
	map<int, int>		   F;
	int					   q = n - 2;
	do
	{
		cout << "? " << max(q--, 0) << '\n' << flush;
		int v, u;
		cin >> v >> u;
		v--;
		u--;
		if (v < 0)
			break;
		V[v] = true;
		D[v]++;
		if (u >= 0)
		{
			E.emplace_back(v, u);
			F.emplace(v, u + 1);
			F.emplace(u, v + 1);
			D[u]++;
		}
	}
	while (q >= -1);
	for (int i = 0; i < n; i++)
		D[i] = V[i] ? min(D[i], 2) : 2;

	vector<int>	 L1, L2, L3;
	vector<bool> V2(n, false);
	for (auto [v, u] : E)
	{
		if (D[v] != 1)
			continue;
		if (u < 0 || D[u] != 1)
			L2.push_back(v);
		else
		{
			L1.push_back(v);
			L3.push_back(u);
			V2[u] = true;
		}
		V2[v] = true;
	}
	vector<int> L;
	copy(begin(L1), end(L1), back_inserter(L));
	copy(begin(L2), end(L2), back_inserter(L));
	copy(begin(L3), end(L3), back_inserter(L));

	set<int> S;
	for (int i = 0; i < n; i++)
		if (!V2[i])
			S.insert(i);

	vector<int> ans{L[0]};
	for (int i = 1; i < (int)size(L); i++)
	{
		int a = L[i - 1], b = L[i];
		int for ()
	}
}
