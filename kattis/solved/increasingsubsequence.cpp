#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	while (cin >> n && n)
	{
		vector<int> X(n);
		for (int &x : X)
			cin >> x;
		vector<int> L(n), P(n, -1);
		int			b = -1;
		for (int i = n - 1; i >= 0; i--)
		{
			for (int j = i + 1; j < n; j++)
			{
				if (X[j] > X[i] && (P[i] < 0 || L[j] + 1 > L[i] || (L[j] + 1 == L[i] && X[j] < X[P[i]])))
				{
					L[i] = L[j] + 1;
					P[i] = j;
				}
			}
			if (b < 0 || L[i] > L[b] || (L[i] == L[b] && X[i] < X[b]))
				b = i;
		}
		vector<int> ans;
		while (b != -1)
		{
			ans.push_back(X[b]);
			b = P[b];
		}
		cout << ans.size();
		for (int x : ans)
			cout << ' ' << x;
		cout << '\n';
	}
}
