#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	while (cin >> n, n >= 0)
	{
		vector<tuple<float, float, float>> P(n);
		for (auto &[x, y, r] : P)
			cin >> x >> y >> r;
		vector<int> vis(n);
		int			ans = 0;
		for (int i = 0; i < n; i++)
			if (!vis[i])
			{
				int		   cur = 0;
				queue<int> Q;
				vis[i] = true;
				Q.push(i);
				while (!Q.empty())
				{
					int v = Q.front();
					Q.pop();
					cur++;
					auto [x, y, r] = P[v];
					for (int w = 0; w < n; w++)
					{
						if (vis[w])
							continue;
						auto [X, Y, R] = P[w];
						float d = hypot(x - X, y - Y);
						if (d + min(r, R) >= max(r, R) && d <= r + R)
						{
							vis[w] = true;
							Q.push(w);
						}
					}
				}
				ans = max(ans, cur);
			}
		cout << "The largest component contains " << ans << (ans != 1 ? " rings.\n" : " ring.\n");
	}
}
