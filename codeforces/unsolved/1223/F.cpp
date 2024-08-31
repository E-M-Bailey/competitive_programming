#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int tc;
	cin >> tc;
	while (tc--)
	{
		int n;
		cin >> n;
		vector<int> A(n);
		for (int &a : A)
			cin >> a;

		vector<int>			  N(n, n + 1), L(n + 2);
		vector<map<int, int>> I(n + 1);
		L[n + 1]	  = -1;
		long long ans = 0;

		for (int i = n; i-- > 0;)
		{
			auto it = I[i + 1].find(A[i]);
			if (it != end(I[i + 1]))
			{
				int j = it->second;
				N[i]  = j + 1;
				if (N[i] < n)
					I[i] = move(I[N[i]]);
			}
			I[i][A[i]] = i;
			ans += (L[i] = L[N[i]] + 1);
		}
		cout << ans << '\n';
	}
}
