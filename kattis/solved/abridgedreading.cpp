#include <bits/stdc++.h>

using namespace std;

vector<int> C;
vector<int> P;
vector<bool> CC;
vector<pair<int, int>> DP;

int main()
{
	int n, m;
	cin >> n >> m;

	C.resize(n);
	P.resize(n, -1);
	CC.resize(n, true);
	DP.resize(n, make_pair(2000000, 2000000));

	for (int &c : C)
		cin >> c;

	while (m--)
	{
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		P[b] = a;
		CC[a] = false;
	}

	for (int i = 0; i < n; i++)
		if (P[i] >= 0)
			C[i] += C[P[i]];

	int ans = 2000000, M = 2000000;

	for (int i = n; i-- > 0;)
	{
		if (CC[i])
		{
			ans = min(ans, M + C[i]);
			M = min(M, C[i]);
			DP[i].first = C[i];
		}
		else
		{
			ans = min(ans, DP[i].first + DP[i].second - C[i]);
		}
		if (P[i] >= 0)
		{
			if (DP[i].first < DP[P[i]].first)
			{
				DP[P[i]].second = DP[P[i]].first;
				DP[P[i]].first = DP[i].first;
			}
			else if (DP[i].first < DP[P[i]].second)
				DP[P[i]].second = DP[i].first;
		}
	}

	cout << ans;
}