#include <bits/stdc++.h>

using namespace std;

int constexpr NUM = 19683;

typedef array<int, 9> state;

vector<pair<int, int>> DP(NUM, {-1, -1});
int					   P3[9]{1};
array<int, 3> constexpr wins[8]{array<int, 3>{0, 1, 2},
								array<int, 3>{3, 4, 5},
								array<int, 3>{6, 7, 8},
								array<int, 3>{0, 3, 6},
								array<int, 3>{1, 4, 7},
								array<int, 3>{2, 5, 8},
								array<int, 3>{0, 4, 8},
								array<int, 3>{2, 4, 6}};

pair<int, int> win_p(state const &S)
{
	for (int p : {1, 2})
		for (auto W : wins)
		{
			bool done = true;
			for (int w : W)
				done &= S[w] == p;
			if (done)
				return p == 2 ? pair{0, 1} : pair{1, 0};
		}
	int ct = 0;
	for (int s : S)
		ct += s == 0;
	if (ct == 0)
		return {0, 0};
	return {-1, -1};
}

pair<int, int> rec(int h, int pl, state &S)
{
	auto &dp = DP[h];
	if (dp.first >= 0)
		return dp;
	dp = win_p(S);
	if (dp.first >= 0)
		return dp;
	dp = {0, 0};
	for (int i = 0; i < 9; i++)
		if (S[i] == 0)
		{
			S[i]		= pl;
			auto [a, b] = rec(h + P3[i] * pl, 3 - pl, S);
			S[i]		= 0;
			dp.first += a;
			dp.second += b;
		}
	return dp;
}

int main()
{
	P3[0] = 1;
	for (int i = 1; i < 9; i++)
		P3[i] = P3[i - 1] * 3;
	state S0{};
	rec(0, 1, S0);

	int t;
	cin >> t;
	while (t--)
	{
		int	  hash = 0;
		state S;
		for (int i = 0; i < 9; i++)
		{
			int	 cur;
			char c;
			cin >> c;
			cur	 = c == '.' ? 0 : c == 'X' ? 1 : 2;
			S[i] = cur;
			hash = hash * 3 + cur;
		}
		auto [a, b] = DP[hash];
		cout << a << ' ' << b << '\n';
	}
}
