#include <bits/stdc++.h>

using namespace std;

struct AhoCorasick
{
	enum { alpha = 256, first = '\0' };
	struct Node
	{
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vector<int> backp;

	void insert(string &s, int j)
	{
		assert(!s.empty());
		int n = 0;
		for (char c : s)
		{
			int &m = N[n].next[c - first];
			if (m == -1) { n = m = (int)size(N); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string> &pat) : N(1, -1)
	{
		for (int i = 0; i < (int)size(pat); i++) insert(pat[i], i);
		N[0].back = (int)size(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop())
		{
			int n = q.front(), prev = N[n].back;
			for (int i = 0; i < alpha; i++)
			{
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else
				{
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vector<int> find(string word)
	{
		int n = 0;
		vector<int> res;
		for (char c : word)
		{
			n = N[n].next[c - first];
			res.push_back(N[n].end);
		}
		return res;
	}
	vector<vector<int>> findAll(vector<string> &pat, string word)
	{
		vector<int> r = find(word);
		//vector<vector<int>> res(size(word));
		vector<vector<int>> res(size(pat));
		for (int i = 0; i < (int)size(word); i++)
		{
			int ind = r[i];
			while (ind != -1)
			{
				//res[i - (int)size(pat[ind]) + 1].push_back(ind);
				res[ind].push_back(i - (int)size(pat[ind]) + 1);
				ind = backp[ind];
			}
		}
		return res;
	}
};

int main()
{
	int n;

	//vector<string> P{"p", "pup"};
	//string W = "Popup";
	//AhoCorasick ac(P);
	//cerr << ac.findAll(P, W).size();

	while (cin >> n)
	{
		string word;
		getline(cin, word);
		vector<string> pat(n);
		for (string &p : pat)
			getline(cin, p);
		getline(cin, word);

		AhoCorasick ac(pat);
		auto ans = ac.findAll(pat, word);
		for (int i = 0; i < n; i++)
		{
			for (auto j : ans[i])
				cout << j << ' ';
			cout << '\n';
		}
	}
}