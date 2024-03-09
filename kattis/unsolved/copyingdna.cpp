#include <bits/stdc++.h>

using namespace std;

int n, m, M;
string S, R, T;
int DP[1 << 18];

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		cin >> S >> T;
		R = string(rbegin(S), rend(S));
		n = (int)S.size();
		m = (int)T.size();
		M = 1 << m;
		fill(DP + 1, DP + M, INT_MAX / 2);
		vector<int> ST;
		for (int i = 0; i < m; i++)
		{
			int l = 0;
			while (i + l + 1 <= n && S.find(T.substr(i, l + 1)) != string::npos || R.find(T.substr(i, l + 1)) != string::npos)
				l++;
			ST.push_back(((1 << l) - 1) << i);
		}
		for (int i = 0; i < M; i++)
			for (int st : ST)
				DP[i | st] = min(DP[i | st], DP[i] + 1);
		for (int i = M; i-- > 0;)
			for (int j = 0; j < m; j++)
				DP[i & ~(1 << j)] = min(DP[i & ~(1 << j)], DP[i] + 1);
		for (int i = 0; i < M; i++)
		{
			
		}
	}
}