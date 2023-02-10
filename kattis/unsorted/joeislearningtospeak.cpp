#include <bits/stdc++.h>

using namespace std;

string lower(const string& s)
{
	string ans;
	ans.reserve(size(s));
	for (char x : s)
		ans.push_back('A' <= x && x <= 'Z' ? x + 32 : x);
	return ans;
}

template<>
struct std::hash<std::vector<int>>
{
	size_t operator()(const std::vector<int>& v) const noexcept
	{
		size_t ans = 0;
		for (int x : v)
			ans = ans * 20011 + x;
		return ans;
	}
};


int main(int argc, const char* argv[])
{
	bool delim[256]{};
	for (char x : { '.', ',', ':', ';', '?', '!', '*', '#' })
		delim[x] = true;
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int lc = 0;
	int n;
	while (cin >> n)
	{
		cout << "Learning case " << ++lc << '\n';
		unordered_set<vector<int>> U;
		unordered_map<string, int> S;
		U.emplace(1, 0);
		S.try_emplace("joe", 0);
		vector<int> C;
		string CS;
		string word;
		bool today = false;
		while (cin >> word)
		{
			char ch = word[0];
			if (delim[ch])
			{
				bool ls = false;
				for (int i = 0; i < size(C); i++)
				{
					for (int j = i + 2; j <= size(C) && j <= i + n; j++)
					{
						ls |= U.emplace(begin(C) + i, begin(C) + j).second;
					}
				}
				if (ls && today)
				{
					cout << "What does the sentence \"" << CS << "\" mean?\n";
				}
				if (ch == '*')
					today = true;
				if (ch == '#')
					break;
				CS.clear();
				C.clear();
				continue;
			}
			if (size(CS))
				CS += ' ';
			CS += word;
			int c = S.try_emplace(lower(word), size(S)).first->second;
			C.push_back(c);
			if (U.emplace(1, c).second && today)
				cout << "What does the word \"" << word << "\" mean?\n";
		}

		cout << endl;
		/*
		unordered_map<string, int> M;
		M["joe"] = 0;
		vector<string> W{ "joe" };
		unordered_set<vector<int>> S;
		vector<int> C;
		string CS;
		string word;
		while (cin >> word, word[0] != '*')
		{
			//cerr << word << endl;
			if (delim[word[0]])
			{
				C.clear();
				continue;
			}
			string lc = lower(word);
			auto pr = M.try_emplace(lc, size(W));
			//cerr << lc << ' '
			auto& [it, ins] = pr;
			if (ins)
			{
				W.push_back(move(lc));
			}
			C.push_back(it->second);
			for (int i = 1; i <= size(C) && i <= n; i++)
			{
				S.emplace(end(C) - i, end(C));
				//for (auto it = end(C) - i; it != end(C); it++)
				//	cerr << *it << ' ';
				//cerr << endl;
			}
		}

		bool ns = false;

		while (cin >> word, word[0] != '#')
		{
			//cerr << word << endl;
			if (delim[word[0]])
			{
				if (ns)
				{
					cout << "What does the sentence \"" << CS << "\" mean?\n";
					ns = false;
				}
				C.clear();
				CS.clear();
				continue;
			}
			string lc = lower(word);
			auto pr = M.try_emplace(lc, size(W));
			auto& [it, ins] = pr;
			//cerr << ' ' << it->first << ' ' << it->second << ' ' << ins << endl;
			if (ins)
			{
				cout << "What does the word \"" << word << "\" mean?\n";
				W.push_back(move(lc));
			}
			C.push_back(it->second);
			if (size(CS))
				CS += ' ';
			CS += word;
			for (int i = 1; i <= size(C) && i <= n; i++)
			{
				ns |= S.emplace(end(C) - i, end(C)).second;
				//cerr << i << ' ' << size(C) << ' ' << n << endl;
				//for (auto it = end(C) - i; it != end(C); it++)
				//	cerr << W[*it] << ' ';
				//cerr << endl;
			}
			//cerr << ns << endl;
		}*/
	}
}