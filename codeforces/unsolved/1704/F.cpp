#include <bits/stdc++.h>

using namespace std;

int DP[500001];

int main()
{
	for (int i = 2; i < 100; i++)
	{
		set<int> S;
		for (int a = 0; a <= i - 2; a++)
			S.insert(DP[a] ^ DP[i - 2 - a]);
		while (S.find(DP[i]) != end(S))
			DP[i]++;
	}
	// Source: https://oeis.org/A002187
	for (int i = 100; i < 500001; i++)
		DP[i] = DP[i - 34];

	int tc;
	cin >> tc;
	while (tc--)
	{
		int n;
		cin >> n;
		vector<bool> G(n);
		for (int i = 0; i < n; i++)
		{
			char c;
			cin >> c;
			G[i] = c == 'B';
		}
		vector<bool> H(n - 1);
		for (int i = 1; i < n; i++)
			H[i - 1] = G[i - 1] ^ G[i];
		int g = 0;
		for (int i = 0; i < n - 1; i++)
		{
			if (!H[i] || (i > 0 && H[i - 1]))
				continue;
			int j = i;
			while (j < n - 1 && H[j])
				j++;
			g ^= DP[j - i + 1];
		}

		int b = accumulate(begin(G), end(G), 0), r = n - b;
		cout << ((g == 0 ? b >= r : b > r) ? "Bob\n" : "Alice\n");
	}
}
