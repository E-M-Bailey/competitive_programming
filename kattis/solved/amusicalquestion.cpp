#include <bits/stdc++.h>

using namespace std;

alignas(1024) array<bitset<1024>, 1024> DP;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int c, n;
	cin >> c >> n;

	DP[0][0] = true;
	while (n--)
	{
		int a;
		cin >> a;
		for (int i = c; i >= 0; i--)
		{
			if (i + a <= c)
				DP[i + a] |= DP[i];
			DP[i] |= DP[i] << a;
		}
	}

	pair<int, int> ans{0, 0};
	for (int a = 0; a <= c; a++)
		for (int b = 0; b <= a; b++)
			if (DP[a][b])
				ans = max(ans, pair{b + a, b - a});
	cout << (ans.first - ans.second) / 2 << ' ' << (ans.first + ans.second) / 2;
}
