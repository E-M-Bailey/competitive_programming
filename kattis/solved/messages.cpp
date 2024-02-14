#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	unordered_set<uint64_t> D[10];

	string ln;

	while (getline(cin, ln), ln != "#")
	{
		uint64_t h = 0;
		int		 n = (int)size(ln);
		for (int i = 0; i < n; i++)
			h = 32 * h + ln[i] - 'a';
		D[n - 1].insert(h);
	}

	string msg;
	vector<int> DP;
	while (getline(cin, ln), ln != "#")
	{
		msg += ln;
		if (msg.back() != '|')
			continue;
		msg.pop_back();
		DP.resize(size(msg) + 1);
		DP[0] = 0;
		uint64_t H[10]{};
		for (int i = 0; i < (int)size(msg); i++)
		{
			for (int k = 9; k > 0; k--)
				H[k] = H[k - 1] * 32 + msg[i] - 'a';
			H[0] = msg[i] - 'a';
			DP[i + 1] = DP[i];
			for (int k = 0; k < 10; k++)
				if (D[k].count(H[k]))
					DP[i + 1] = max(DP[i + 1], DP[i - k] + 1);
		}
		cout << DP.back() << '\n';
		msg.clear();
	}
}
