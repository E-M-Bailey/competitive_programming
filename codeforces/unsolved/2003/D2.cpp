#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		vector<int> M1(n), M2(n);
		vector<int> A;
		for (int i = 0; i < n; i++)
		{
			int l;
			cin >> l;
			A.resize(l);
			for (int &a : A)
				cin >> a;
			sort(begin(A), end(A));
			A.erase(unique(begin(A), end(A)), end(A));
			l = (int)size(A);
			int ptr = 0;
			while (ptr < l && A[ptr] == M1[i])
			{
				M1[i]++;
				ptr++;
			}
			M2[i] = M1[i] + 1;
			while (ptr < l && A[ptr] == M2[i])
			{
				M2[i]++;
				ptr++;
			}
		}
		
		int M = *max_element(begin(M2), end(M2));

		vector<vector<int>> G(M + 1);
		for (int i = 0; i < n; i++)
			G[M1[i]].push_back(M2[i]);
		
		int d = 0;
		vector<int> DP(M + 1);
		for (int i = M + 1; i-- > 0;)
		{
			DP[i] = i;
			for (int v : G[i])
				DP[i] = max(DP[i], DP[v]);
			switch (size(G[i]))
			{
			case 0:
				break;
			case 1:
				d = max(d, i);
				break;
			default:
				d = max(d, DP[i]);
				break;
			}
		}

		long long ans = (long long)m * (m + 1) / 2;
		for (int i = 0; i <= min(m, M); i++)
			ans += max(DP[i], d) - i;
		cout << ans << '\n';
	}
}

