#include <bits/stdc++.h>

using namespace std;

/*
vector<uint64_t> cmp(int seed, int n)
{
	mt19937_64 randy(seed);
	uniform_int_distribution<int> didx(0, 9);
	uniform_int_distribution<int> dch(1, 26);
	unordered_set<uint64_t> M;
	vector<uint64_t> ans;
	ans.reserve(n);

	while (!ans.empty() && ans.size() < n)
	{
		int i = ans.size();
		int idx = didx(randy);
		int ch = dch(randy);

	}
	return ans;
}*/

mt19937_64 randy(12390198);
uniform_int_distribution<int> didx(0, 9);
uniform_int_distribution<char> dch('a', 'z');

constexpr int MAXT = 4;

unordered_set<string> AV;

vector<string> gen()
{
	array<bool, 5> d{};
	vector<string> ans{"aaaaa"};
	while (size(ans) < 2501)
	{
		string s = ans.back();
		for (int i = 0; i < 5; i++)
		{
			if (s[i] == (d[i] ? 'a' : 'z'))
			{
				d[i] ^= 1;
				continue;
			}
			s[i] += d[i] ? -1 : 1;
			break;
		}
		ans.push_back(s);
	}
	return ans;
}

int main()
{
	vector<string> S = gen();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cout << S[i / 2] << S[(i + 1) / 2] << endl;
}