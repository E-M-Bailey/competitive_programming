#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	unordered_map<int, int> F;
	F.reserve(n * m);
	vector<int> S(n);
	for (auto &s : S)
		cin >> s;
	for (int i = 0; i < m; i++)
	{
		int e;
		cin >> e;
		for (int s : S)
		{
			int d = e - s;
			if (d >= 0)
				F[d]++;
			else
				break;
		}
	}
	int best = 0, bestf = 0;
	for (auto [t, f] : F)
		if (make_pair(f, -t) > make_pair(bestf, -best))
			tie(bestf, best) = make_pair(f, t);
	cout << best;
}