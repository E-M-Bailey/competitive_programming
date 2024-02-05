#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> PA{};

int n, t, m;

vector<int> A;

struct state
{
	int	 a, b;
	bool operator<(state s) const
	{
		int d1 = a - b, d2 = s.a - s.b;
		if (d1 != d2)
			return d1 < d2;
		return a < s.a;
	}
	template<bool B>
	state incr()
	{
		state ans = *this;
		(B ? ans.b : ans.a)++;
		return ans;
	}
};

vector<vector<vector<state>>> DP;

const int HT = 46;

state f(int i, int tn, int cons)
{
	if (i == 0)
		if (cons == 0)
			return {0, 0};
		else
			return {-100000000, 100000000};

	state &dp = DP[i - 1][tn][cons + 4];
	if (dp.a != -1)
		return dp;

	state ans{-100000000, 100000000};
	int	  a = A[i - 1];
	// Let other team win this minute
	if (a > 0 && cons <= 0)
	{
		if (i == HT)
		{
			if (cons == -1)
				for (int c = -4; c <= 4; c++)
					ans = max(ans, f(i - 1, tn, c));
		}
		else if (cons < 0)
		{
			ans = max(ans, f(i - 1, tn, cons + 1));
			if (cons == -1)
				for (int c = 1; c <= 4; c++)
					ans = max(ans, f(i - 1, tn, c));
		}
		else if (cons == 0)
			ans = max(ans, f(i - 1, tn, -4).incr<1>());
	}
	// Tie this minute
	if (tn >= a && a <= n && cons == 0)
	{
		if (cons == 0)
			for (int c = -4; c <= 4; c++)
				ans = max(ans, f(i - 1, tn - a, c));
	}
	// Win this minute
	if (tn > a && a < n && cons >= 0)
	{
		if (i == HT)
		{
			if (cons == 1)
				for (int c = -4; c <= 4; c++)
					ans = max(ans, f(i - 1, tn - 1 - a, c));
		}
		else if (cons > 0)
		{
			ans = max(ans, f(i - 1, tn - 1 - a, cons - 1));
			if (cons == 1)
				for (int c = -4; c <= -1; c++)
					ans = max(ans, f(i - 1, tn - 1 - a, c));
		}
		else if (cons == 0)
			ans = max(ans, f(i - 1, tn - 1 - a, 4).incr<0>());
	}

	return dp = ans;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> t >> m;
	A.resize(90, 0);
	for (int i = 0; i < m; i++)
	{
		int a, b;
		cin >> a >> b;
		for (int j = a; j < b; j++)
			A[j]++;
	}

	DP.assign(90, vector<vector<state>>(t * n + 1, vector<state>(9, state{-1, -1})));

	state ans{-100000000, 100000000};
	for (int c = -4; c <= 4; c++)
		ans = max(f(90, t * n, c), ans);

	cout << ans.a << ' ' << ans.b << '\n';
}
