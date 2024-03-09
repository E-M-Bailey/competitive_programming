#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k;

	vector<int> P(n);
	for (int i = 1; i < n; i++)
	{
		cin >> P[i];
		P[i]--;
	}

	vector<int> S(n);

	int lo = 0, hi = n;
	while (lo < hi)
	{
		int mid	 = (lo + hi) / 2;
		int cost = 0;
		fill(begin(S), end(S), 1);
		for (int i = n; i-- > 0;)
		{
			if (S[i] > mid)
				cost++;
			else
				S[P[i]] += S[i];
		}
		if (cost > k)
			lo = mid + 1;
		else
			hi = mid;
	}
	cout << lo;
}
