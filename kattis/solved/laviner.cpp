#include <bits/stdc++.h>
using namespace std;
int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, k;
	cin >> n >> k;
	int P[n], S[n], l = 0, h = n + 1;
	for (int i = 1; i < n; i++)
		cin >> P[i];
	while (h - l > 1)
	{
		int m = (l + h - 1) / 2, c = 0;
		fill_n(S, n, 1);
		for (int i = n; i--;)
			if (S[i] > m)
				c++;
			else
				S[P[i] - 1] += S[i];
		(c > k ? l : h) = m + 1;
	}
	cout << l;
}
