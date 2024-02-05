#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n, K;
	cin >> n >> K;
	vector<int>			P(n);
	vector<vector<int>> C(n);
	for (int i = 0; i < n; i++)
	{
		cin >> P[i];
		P[i]--;
		C[P[i]].push_back(i);
	}
	vector<vector<int>>		CY;
	unordered_map<int, int> CI;
	{
		vector<bool>			V(n, false);
		vector<int>				stck;
		unordered_map<int, int> I;
		for (int i = 0; i < n; i++)
		{
			if (V[i])
				continue;
			int j = i;
			for (; !V[j]; j = P[j])
			{
				V[j] = true;
				I[j] = stck.size();
				stck.push_back(j);
			}
			int ci;
			if (I.find(j) != I.end())
			{
				ci = CY.size();
				CY.emplace_back(stck.begin() + I[j], stck.end());
			}
			else
				ci = CI[j];
			for (int k : stck)
				CI[k] = ci;
			stck.clear();
			I.clear();
		}
	}
	int					   m = CY.size();
	vector<pair<int, int>> IV(m);
	for (int i = 0; i < m; i++)
		IV[i].first = CY[i].size();
	for (int i = 0; i < n; i++)
		IV[CI[i]].second++;

	vector<bool> KP(K + 1, false);
	KP[0] = true;
	for (int i = 0; i < m; i++)
		for (int j = K; j >= 0; j--)
			if (KP[j])
				for (int k = j + IV[i].first; k <= min(K, j + IV[i].second); k++)
					KP[k] = true;

	for (int i = K; i >= 0; i--)
		if (KP[i])
		{
			cout << i;
			break;
		}
}
