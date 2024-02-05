#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, d, s, t, f, F;
	cin >> n >> d >> s >> t >> f >> F;

	vector<int>	   I;
	vector<double> C;

	for (int cross = 1 << (n - 1) | 1; cross < 1 << n; cross += 2)
	{
		int m = __builtin_popcount(cross);
		I.clear();
		I.reserve(m);
		for (int i = 0; i < n; i++)
			if (cross & (1 << i))
				I.push_back(i);
		do
		{
			int adj = 0;
			for (int i = 0; i < m - 1; i++)
				if (abs(I[i] - I[i + 1]) == 1)
					adj |= 1 << i;

			int nocrosses = 0;
			do
			{
				nocrosses	= (int)((unsigned)nocrosses - 1) & adj;
				double cost = s + t * 2 * m;
				for (int i = 0; i < m - 1; i++)
				{
					int dist = d * abs(I[i] - I[i + 1]);
					cost += nocrosses & (1 << i) ? 2 * dist : 2 * sqrt(dist * dist + s * s);
				}
				C.push_back(cost);
			}
			while (nocrosses);
		}
		while (next_permutation(begin(I) + 1, end(I) - 1));
	}

	sort(begin(C), end(C));

	int l;
	while (cin >> l)
	{
		int lo = l - 2 * F, hi = l - 2 * f;
		cout << lower_bound(begin(C), end(C), hi) - lower_bound(begin(C), end(C), lo) << '\n';
	}
}
