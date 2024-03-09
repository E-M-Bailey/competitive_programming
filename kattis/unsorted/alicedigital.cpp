#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t, n, m;
	vector<int> A, R;
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		A.resize(n);
		R.resize(n);
		for (int &a : A)
			cin >> a;

		int ans = 0;
		int r = n;
		for (int i = n; i-- > 0;)
		{
			R[i] = r;
			if (A[i] <= m)
				r = i;
		}
		int l = 0;
		for (int i = 0; i < n; i++)
		{
			if (A[i] == m)
				ans = max(ans, accumulate(begin(A) + l, begin(A) + R[i], 0));
			if (A[i] <= m)
				l = i + 1;
		}
		cout << ans << '\n';
		
	}

}