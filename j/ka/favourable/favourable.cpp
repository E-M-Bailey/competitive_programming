#include <bits/stdc++.h>

using namespace std;
int G[400][3];
int S[400];
int64_t DP[400];

int64_t f(int v)
{
	return DP[v] = DP[v] < 0 ? G[v][0] < 0 ? G[v][0] + 2 : f(G[v][0]) + f(G[v][1]) + f(G[v][2]) : DP[v];
}

int main()
{
	int T;
	cin >> T;
	string str;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cin >> S[i] >> str;
			S[i]--;
			if (str == "favourably")
				G[S[i]][0] = -1;
			else if (str == "catastrophically")
				G[S[i]][0] = -2;
			else
			{
				G[S[i]][0] = atoi(str.c_str()) - 1;
				cin >> G[S[i]][1] >> G[S[i]][2];
				G[S[i]][1]--;
				G[S[i]][2]--;
			}
			DP[S[i]] = -1;
		}
		cout << f(0) << '\n';
	}
}