#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1e9 + 7;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, l;
	cin >> n >> l;
	vector<int> G(l);

	int	 p	   = -1;
	bool valid = true;
	for (int &g : G)
	{
		cin >> g;
		g--;
		if (g <= p)
			valid = false;
		p = g;
	}
	if (p != n - 1)
		valid = false;
	if (!valid)
	{
		cout << 0 << '\n';
		return 0;
	}

	int64_t r = 0, ans = 1;

	for (int i = n - 1; i >= 0; i--)
	{
		if ((int)size(G) && i == G.back())
			G.pop_back();
		else
			ans = ans * r % MOD;
		r++;
	}
	cout << ans;
}
