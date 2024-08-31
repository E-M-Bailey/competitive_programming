#include <bits/stdc++.h>

using namespace std;

long long constexpr MOD = 998244353;
long long ans			= 0;
int		  n;
long long A, B, C;

int constexpr LIM = 300;

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int q;
	cin >> n >> q;

	vector<unordered_set<int>>		G(n);
	vector<int>						BL;
	vector<unordered_map<int, int>> big(n);

	for (int i = 0; i < q; i++)
	{
		cin >> A >> B >> C;
		int a = int(1 + ((A * (1 + ans)) % MOD) % 2);
		int b = int(((B * (1 + ans)) % MOD) % n);
		int c = int(((C * (1 + ans)) % MOD) % n);

		if (a == 1)
		{
			G[b].insert(c);
			G[c].insert(b);

			if (size(G[b]) == LIM)
				BL.push_back(b);
			if (size(G[c]) == LIM)
				BL.push_back(c);

			if (size(G[b]) >= LIM)
				for (int w : BL)
					if (w != b && G[w].find(c) != end(G[w]))
						big[b][w] = big[w][b] = c + 1;
			if (size(G[c]) >= LIM)
				for (int w : BL)
					if (w != c && G[w].find(b) != end(G[w]))
						big[c][w] = big[w][c] = b + 1;

			if (size(G[b]) == LIM)
				for (int w : G[b])
					for (int x : G[w])
						if (x != b && size(G[x]) >= LIM)
							big[b][x] = big[x][b] = w + 1;
			if (size(G[c]) == LIM)
				for (int w : G[c])
					for (int x : G[w])
						if (x != c && size(G[x]) >= LIM)
							big[c][x] = big[x][c] = w + 1;
		}
		else
		{
			int db = (int)size(G[b]), dc = (int)size(G[c]);
			if (db > dc)
			{
				swap(b, c);
				swap(db, dc);
			}
			if (db < LIM)
			{
				ans = 0;
				for (int w : G[b])
					if (G[c].find(w) != end(G[c]))
					{
						ans = w + 1;
						break;
					}
			}
			else
				ans = big[b][c];
			cout << ans << '\n';
		}
	}
}
