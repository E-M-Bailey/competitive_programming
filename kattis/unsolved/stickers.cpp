#include <bits/stdc++.h>

using namespace std;

string msg;
int n, m;

vector<vector<unordered_map<int, int>>> DP;

vector<int> L;
vector<vector<int>> M;
vector<int> C;

int dp(int i, int l, int mask)
{
	if (i + l > n)
		return INT_MAX / 2;
	if (i == n && l == 0)
		return 0;
	auto [dpit, dpins] = DP[i][l].try_emplace(mask, -1);
	if (!dpins)
		return dpit->second;
}

int main()
{
	cin >> msg >> m;
	n = (int)msg.size();
	DP.assign(n, vector<unordered_map<int, int>>(21));
	M.resize(m);
	C.resize(m);
	L.resize(m);
	for (int i = 0; i < m; i++)
	{
		string s;
		cin >> s >> C[i];
		M[i].resize(n);
		L[i] = (int)s.size();
		for (int j = 0; j + L[i] <= n; j++)
		{
			for (int k = 0; k < L[i]; k++)
				M[i][j] |= int(msg[j + k] == s[i])
					M[i][j] |= 1 << k;
		}
	}
}