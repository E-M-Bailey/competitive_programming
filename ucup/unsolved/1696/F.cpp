#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<vector<long long>> P(31, vector<long long>(31));
	P[0][0] = 1;
	for (int i = 1; i < 31; i++)
	{
		P[i][0] = P[i - 1][0];
		for (int j = 1; j < 31; j++)
			P[i][j] = P[i - 1][j - 1] + P[i - 1][j];
	}
	
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		vector<pair<int, int>> A(n);
		for (auto &[x, y] : A)
			cin >> x >> y;
		
		vector<vector<long long>> M(30, vector<long long>(2 * n));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				M[i][j] = P[i][A[j].first];
		}
	}
}
