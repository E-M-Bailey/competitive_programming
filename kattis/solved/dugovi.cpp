#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	long long ans = 0;
	vector<int> P(n), I(n);
	vector<long long> need(n), out(n);
	for (int v = 0; v < n; v++)
	{
		cin >> P[v] >> need[v];
		out[v] = need[v];
		P[v]--;
		I[P[v]]++;
	}

	vector<int> L;
	for (int v = 0; v < n; v++)
		if (I[v] == 0)
			L.push_back(v);
	
	vector<bool> vis(n);

	while (!L.empty())
	{
		int v = L.back();
		L.pop_back();
		vis[v] = true;
		ans += need[v];

		int w = P[v];
		need[w] = max(0ll, need[w] - out[v]);
		if (--I[w] == 0)
			L.push_back(w);
	}

	vector<int> CC;

	for (int i = 0; i < n; i++)
		if (!vis[i])
		{
			CC = {i};
			do
				CC.push_back(P[CC.back()]);
			while (CC.back() != i);
		
			int m = (int)size(CC) - 1;
			long long sum = 0;
			for (int j = 0; j < m; j++)
				sum += max(0ll, need[CC[j + 1]] - out[CC[j]]);
			
			long long cur = LLONG_MAX;
			for (int j = 0; j < m; j++)
				cur = min(cur, sum - max(0ll, need[CC[j + 1]] - out[CC[j]]) + need[CC[j + 1]]);
			
			ans += cur;
			for (int v : CC)
				vis[v] = true;
		}
	cout << ans;
}
