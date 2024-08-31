#include <bits/stdc++.h>

using namespace std;

int m;

vector<int> enc(int c)
{
	vector<int> ans;
	for (int i = 0; i < m; i++)
		if (c & (1 << i))
			ans.push_back(i);
	return ans;
}

int main()
{
	int k, c;
	cin >> m >> k >> c;
	vector<pair<vector<int>, int>> K;
	for (int i = 0; i < (1 << m); i++)
		if (__builtin_popcount(i) == k)
			K.emplace_back(enc(i), i);
	sort(begin(K), end(K));
	// for (auto k : K)
	// {
	// 	for (int e : k.first)
	// 		cerr << e << ' ';
	// 	cerr << endl;
	// }
	string ln;
	getline(cin, ln);
	int			ck = -1, cor = 0, s = 0, i = -1, ct = 0;
	vector<int> ans;
	while (getline(cin, ln))
	{
		if (ln.empty())
			continue;
		i++;
		ct++;
		// cerr << i << ' ' << size(ln) << ' ' << ln << endl;
		istringstream strm(string{begin(ln) + 1, end(ln) - 1});
		int			  ch = 0;
		{
			int c;
			while (strm >> c)
				ch |= 1 << c;
		}

		if (ck >= 0)
		{
			if ((K[ck].second & ch) == ch)
			{
				ct--;
				cout << ck << '\n';
				continue;
			}
			s	= i;
			ck	= -1;
			cor = 0;
		}

		cor |= ch;
		if (__builtin_popcount(cor) > k)
		{
			for (int j = s; j <= i; j++)
			{
				ct--;
				cout << "?\n";
			}
			s = i;
			continue;
		}
		else if (__builtin_popcount(cor) == k)
		{
			ck = int(lower_bound(begin(K), end(K), pair{enc(cor), cor}) - begin(K));
			for (int j = s; j <= i; j++)
			{
				ct--;
				cout << ck << "\n";
			}
			s = i;
			continue;
		}
	}
	for (int j = 0; j < ct; j++)
		cout << "?\n";
}
