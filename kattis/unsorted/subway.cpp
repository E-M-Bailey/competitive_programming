#include <bits/stdc++.h>
using namespace std;

ostringstream ans;

struct trie
{
	vector<unordered_map<int, int>> N;
	trie(): N(1) {}

	int insert(const vector<int>& A)
	{
		//err << "adding";
		//for (int a : A)
		//	err << ' ' << a;
		//err << endl;
		int i = 0;
		for (int a : A)
		{
			auto [it, ins] = N[i].emplace(a, N.size());
			if (ins)
				N.emplace_back();
			i = it->second;
		}
		//err << ' ' << i << endl;
		return i;
	}
};

int dfs(const string& s, trie& T, int& i)
{
	int og = i;
	i++;
	vector<int> A;
	while (s[i] == '0')
		A.push_back(dfs(s, T, i));
	sort(A.begin(), A.end());
	i++;
	//err << " parsed " << s.substr(og, i - og) << endl;
	return T.insert(A);
}

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		string s, t;
		cin >> s >> t;
		s = "0" + s + "1";
		t = "0" + t + "1";
		trie T;
		int i = 0, j = 0;
		int x = dfs(s, T, i);
		int y = dfs(t, T, j);
		//err << x << ' ' << y << endl;
		ans << (x == y ? "same\n" : "different\n");
	}
	cout << ans.str();
}

/*
2
0010011101001011
0100011011001011
0100101100100111
0011000111010101

*/

/*
	int n;
	cin >> n;
	int a;
	cin >> a;
	vector<vector<pair<int, int64_t>>> A(n);
	for (int i = 0; i < a; i++)
	{
		int u, v;
		int64_t t;
		cin >> u >> v >> t;
		A[u].
	}
*/