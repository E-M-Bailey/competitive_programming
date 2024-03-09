#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> G(n);
	int m;
	cin >> m;
	while (m--)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		G[a] |= 1 << b;
		G[b] |= 1 << a;
	}

	int ans = 0;
	for (int mask = 0; mask < (1 << n); mask++)
	{
		int bad = 0;
		for (int i = 0; i < n; i++)
			if (mask & (1 << i))
				bad |= G[i];
		ans += ((bad & mask) == 0);
	}
	cout << ans;
}