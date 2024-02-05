#include <bits/stdc++.h>

using namespace std;

string const W[]{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int constexpr MOD = 9302023;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	vector<pair<int, int>> R;
	string				   s;
	cin >> s;
	int n = (int)s.size();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 10; j++)
			if (i + W[j].size() <= s.size() && s.substr(i, W[j].size()) == W[j])
				R.emplace_back(i, i + (int)W[j].size());
	vector<vector<int>> C;
	int					p = 0;
	for (auto [l, r] : R)
	{
		if (l >= p)
			C.emplace_back();
		C.back().push_back(r - l - 1);
		p = r;
	}
	int ans1 = n, ans2 = 1;
	for (auto const &CC : C)
	{
		int a = 0, b = 0, c = 0;
		int x = 0, y = 1, z = 0;

		for (int l : CC)
		{
			if (a < b)
				x = y;
			else if (a == b)
				x = (x + y) % MOD;
			a = max(a, b);
			b = c;
			y = z;
			c = a + l;
			z = x;
		}
		ans1 -= max(b, c);
		ans2 = (int)(((long long)ans2 * (b < c ? z : b > c ? y : y + z)) % MOD);
	}
	cout << ans1 << '\n' << ans2;
}
