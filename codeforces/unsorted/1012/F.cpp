#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	// cin >> tc;
	while (tc--)
		go();
}

#define ALL(C) begin(C), end(C)

int n;

int DP[1 << 22];
int P[1 << 22];

map<int, int>		   LR;
vector<pair<int, int>> T;

int r(int t)
{
	auto it = LR.upper_bound(t);
	if (it == begin(LR))
		return t;
	--it;
	if (it->second <= t)
		return t;
	return it->second = r(it->second);
}

int f(int S)
{
	int &dp = DP[S];
	if (dp < 0)
	{
		dp = INT_MAX / 2;
		for (int a = 0; a < n; a++)
			if (S & (1 << a))
			{
				int cur = T[a].second + r(f(S ^ (1 << a)));
				if (cur < T[a].first && cur < dp)
				{
					dp	 = cur;
					P[S] = a;
				}
			}
	}
	return dp;
}

void backtrack(int S, int tag, vector<pair<int, int>> &ans)
{
	if (S > 0)
	{
		int a = P[S];
		backtrack(S ^ (1 << a), tag, ans);
		ans[a] = {tag, r(f(S ^ (1 << a)))};
	}
}

void go()
{
	fill(ALL(DP), -1);
	DP[0] = 1;
	int p;
	cin >> n >> p;
	int N = (1 << n) - 1;

	for (int i = 0; i < n; i++)
	{
		int s, l, t;
		cin >> s >> l >> t;
		LR.emplace(s, s + l);
		T.emplace_back(s, t);
	}

	int lim = p == 1 ? 1 : 1 << n;
	for (int S = 0; S < lim; S++)
	{
		int S2	= N ^ S;
		int cur = max(f(S2), f(S));
		if (cur < INT_MAX / 2)
		{
			vector<pair<int, int>> ans(n);
			backtrack(S, 2, ans);
			backtrack(S2, 1, ans);
			cout << "YES\n";
			for (auto [tag, t] : ans)
				cout << tag << ' ' << t << '\n';
			return;
		}
	}
	cout << "NO\n";
}
