#include <bits/stdc++.h>

using namespace std;

pair<int, int> const DIR[4]{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int TC;
	cin >> TC;
	int L[6001], R[6001];
	for (int tc = 1; tc <= TC; tc++)
	{
		cout << "Case #" << tc << ": ";
		string path;
		int	   n;
		cin >> n;
		while (n--)
		{
			string s;
			int	   t;
			cin >> s >> t;
			while (t--)
				path += s;
		}
		{
			int l = 0;
			for (char c : path)
			{
				l += c == 'L';
				l -= c == 'R';
			}
			if (l < 0)
				for (char &c : path)
				{
					if (c == 'L')
						c = 'R';
					else if (c == 'R')
						c = 'L';
				}
		}

		fill(begin(L), end(L), 6000);
		fill(begin(R), end(R), 0);
		int ans = 0;
		int x = 3000, y = 3000, d = 0;
		for (char c : path)
		{
			if (c == 'L')
			{
				if (++d == 4)
					d = 0;
			}
			else if (c == 'R')
			{
				if (--d == -1)
					d = 3;
			}
			else
			{
				int px = x, py = y;
				x += DIR[d].first;
				y += DIR[d].second;
				ans += px * y - x * py;
				if (d == 0)
				{
					L[py] = min(L[py], x);
					R[py] = max(R[py], x);
				}
				else if (d == 2)
				{
					L[y] = min(L[y], x);
					R[y] = max(R[y], x);
				}
			}
		}
		ans /= 2;

		int lo = 0, hi = 6000;
		while (L[lo] > R[lo])
			lo++;
		while (L[hi] > R[hi])
			hi--;

		for (int a = lo, b = hi; a < b;)
		{
			if (L[b] <= L[a])
			{
				L[a + 1] = min(L[a + 1], L[a]);
				a++;
			}
			else
			{
				L[b - 1] = min(L[b - 1], L[b]);
				b--;
			}
		}
		for (int a = lo, b = hi; a < b;)
		{
			if (R[b] >= R[a])
			{
				R[a + 1] = max(R[a + 1], R[a]);
				a++;
			}
			else
			{
				R[b - 1] = max(R[b - 1], R[b]);
				b--;
			}
		}

		for (int i = lo; i <= hi; i++)
			ans += R[i] - L[i];

		cout << ans << '\n';
	}
}
