#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> L;

constexpr uint64_t A1 = 1010003, A2 = 1010033, M1 = 1e9 + 9, M2 = 1e9 + 7;

struct fragment
{
	vector<int>		D;
	int				n;
	friend istream &operator>>(istream &is, fragment &F)
	{
		static string ln, ln2;
		while (getline(is, ln), ln != "***END***")
		{
			while (!ln.empty() && ln.back() == ' ')
				ln.pop_back();
			if (ln.empty())
				continue;

			auto it = ln.begin();
			while (*it == ' ')
				++it;
			ln.erase(ln.begin(), it);

			ln2.clear();
			for (char c : ln)
				if (c != ' ' || ln2.empty() || ln2.back() != ' ')
					ln2.push_back(c);
			F.D.push_back(L.try_emplace(move(ln2), (int)L.size()).first->second);
		}
		F.n = (int)F.D.size();
		return is;
	}

	void hashes(int len, unordered_set<uint64_t> &H) const
	{
		H.clear();
		uint64_t h1 = 0, h2 = 0, p1 = M1 - 1, p2 = M2 - 1;
		for (int i = 0; i < len; i++)
		{
			h1 = (A1 * h1 + D[i]) % M1;
			h2 = (A2 * h2 + D[i]) % M2;
			p1 = p1 * A1 % M1;
			p2 = p2 * A2 % M2;
		}
		H.insert(h1 << 32 | h2);

		for (int i = len; i < n; i++)
		{
			h1 = (A1 * h1 + D[i] + p1 * D[i - len]) % M1;
			h2 = (A2 * h2 + D[i] + p2 * D[i - len]) % M2;
			H.insert(h1 << 32 | h2);
		}
	}

	bool matches(int len, unordered_set<uint64_t> const &H) const
	{
		uint64_t h1 = 0, h2 = 0, p1 = M1 - 1, p2 = M2 - 1;
		for (int i = 0; i < len; i++)
		{
			h1 = (A1 * h1 + D[i]) % M1;
			h2 = (A2 * h2 + D[i]) % M2;
			p1 = p1 * A1 % M1;
			p2 = p2 * A2 % M2;
		}
		if (H.find(h1 << 32 | h2) != H.end())
			return true;

		for (int i = len; i < n; i++)
		{
			h1 = (A1 * h1 + D[i] + p1 * D[i - len]) % M1;
			h2 = (A2 * h2 + D[i] + p2 * D[i - len]) % M2;
			if (H.find(h1 << 32 | h2) != H.end())
				return true;
		}
		return false;
	}
};

int main()
{
	int n;
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<string>	 names(n);
	vector<fragment> frags(n);
	fragment		 src;
	int				 hi = 0;

	for (int i = 0; i < n; i++)
	{
		getline(cin, names[i]) >> frags[i];
		hi = max(hi, frags[i].n);
	}
	cin >> src;

	int						lo = 0;
	vector<int>				fnd, ans;
	unordered_set<uint64_t> H;
	while (lo < hi)
	{
		int mid = (lo + hi + 1) / 2;
		fnd.clear();
		src.hashes(mid, H);
		for (int i = 0; i < n; i++)
			if (frags[i].matches(mid, H))
				fnd.push_back(i);
		if (fnd.empty())
			hi = mid - 1;
		else
		{
			lo = mid;
			ans.swap(fnd);
		}
	}

	cout << lo;
	for (int i : ans)
		cout << ' ' << names[i];
}
