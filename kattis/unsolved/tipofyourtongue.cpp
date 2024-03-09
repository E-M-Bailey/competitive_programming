#include <bits/stdc++.h>

using namespace std;

struct trie
{
	struct node
	{
		int ch[26];
		int ct;
		node() : ch{}, ct(0)
		{
			fill(begin(ch), end(ch), -1);
		}
	};
	vector<node> N;

	void add(const string &str) {
		int ptr = 0;
		for (char c : str)
		{
			N[ptr].ct++;
			int &nxt = N[ptr].ch[c - 'a'];
			if (nxt < 0)
			{
				nxt = (int)size(N);
				N.emplace_back();
			}
			nxt = 
		}
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	vector<string> S(n), T(n), U(n);
	for (int i = 0; i < n; i++)
	{
		string &s = S[i], &t = T[i], &u = U[i];
		cin >> t;
		int m = (int)size(t);
		s.resize(m * 2);
		u.resize(m);
		for (int j = 0; j < m; j++)
		{
			s[j * 2]	 = t[j];
			s[j * 2 + 1] = u[j] = t[m - 1 - j];
		}
	}
	sort(begin(S), end(S));
	sort(begin(T), end(T));
	sort(begin(U), end(U));

	auto const freq = [&](string &pat, vector<string> const &dict)
	{
		auto lo = lower_bound(begin(dict), end(dict), pat);
		pat.push_back(char('z' + 1));
		auto hi = lower_bound(lo, end(dict), pat);
		pat.pop_back();
		return int(hi - lo);
	};

	string code, pre, suf, pat;
	while (q--)
	{
		cin >> code >> pre >> suf;
		int m = (int)size(pre);
		pat.resize(m * 2);
		reverse(begin(suf), end(suf));
		for (int i = 0; i < m; i++)
		{
			pat[i * 2]	   = pre[i];
			pat[i * 2 + 1] = suf[i];
		}
		if (code[0] == 'A')
			cout << freq(pat, S) << '\n';
		else if (code[0] == 'O')
			cout << freq(pre, T) + freq(suf, U) - freq(pat, S) << '\n';
		else
			cout << freq(pre, T) + freq(suf, U) - 2 * freq(pat, S) << '\n';
	}
}
