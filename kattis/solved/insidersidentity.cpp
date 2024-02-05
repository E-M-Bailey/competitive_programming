#include <bits/stdc++.h>

using namespace std;

typedef array<int, 2> node;
typedef vector<node>  vnode;
constexpr node		  MT{-1, -1};

struct DFA
{
	int			 n, m = 0;
	string		 S;
	vnode		 G;
	vector<bool> L;

	int mkTrie(int i = 0)
	{
		int v = G.size();
		G.push_back(MT);
		L.push_back(i == n);
		if (i < n)
		{
			char c = S[i];
			if (c == '*')
				G[v][0] = mkTrie(i + 1);
			G[v][1] = mkTrie(i + 1);
		}
		return v;
	}

	vector<int> mkSLinks()
	{
		vector<int> SL(m);
		SL[0] = 0;
		queue<pair<int, int>> Q;
		Q.emplace(0, 0);
		while (!Q.empty())
		{
			auto [u, v] = Q.front();
			Q.pop();
			if (v == -1)
				continue;
			bool o = G[u][1] == v;
			if (u == 0)
				SL[v] = 0;
			else
			{
				do
					u = SL[u];
				while (u != 0 && G[u][o] == -1);
				if (G[u][o] == -1)
					SL[v] = 0;
				else
					SL[v] = G[u][o];
			}
			Q.emplace(v, G[v][0]);
			Q.emplace(v, G[v][1]);
		}
		return SL;
	}

	void addSLinks()
	{
		vector<int> SL	 = mkSLinks();
		const auto	next = [&](int v, bool o)
		{
			if (v == 0)
				return 0;
			while (v != 0 && G[v][o] == -1)
				v = SL[v];
			if (G[v][o] == -1)
				return 0;
			else
				return G[v][o];
		};
		for (int i = 0; i < m; i++)
		{
			if (G[i][0] == -1)
				G[i][0] = next(i, 0);
			if (G[i][1] == -1)
				G[i][1] = next(i, 1);
		}
	}

	DFA(const string &S) : n(S.size()), S(S)
	{
		mkTrie();
		m = G.size();
		addSLinks();
	}

	int64_t count(int n)
	{
		vector<int64_t> C(m, 0), C2(m);
		C[0]		= 1;
		int64_t ans = 0;
		for (int i = 0; i <= n; i++)
		{
			ans *= 2;
			fill(begin(C2), end(C2), 0);
			for (int j = 0; j < m; j++)
				if (L[j])
					ans += C[j];
				else
				{
					C2[G[j][0]] += C[j];
					C2[G[j][1]] += C[j];
				}
			swap(C, C2);
		}
		return ans;
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	string P;
	getline(cin, P);
	getline(cin, P);
	DFA dfa(P);
	cout << dfa.count(n);
}
