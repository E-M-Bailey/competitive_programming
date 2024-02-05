#include <bits/stdc++.h>

using namespace std;

bool incr(vector<int> &I, int &d, const vector<int> &M, const vector<vector<int>> &PP)
{
	int n = (int)I.size();
	for (int i = 0; i < n; i++)
	{
		I[i]++;
		d *= PP[i][0];
		if (I[i] <= M[i])
			return true;
		I[i] = 0;
		d /= PP[i].back();
	}
	return false;
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int V;
	cin >> V;
	vector<int> P, M;

	{
		int V2 = V;
		for (int p = 2; p * p <= V; p++)
		{
			if (V % p != 0)
				continue;
			P.push_back(p);
			M.push_back(0);
			while (V % p == 0)
			{
				M.back()++;
				V /= p;
			}
		}
		if (V > 1)
		{
			P.push_back(V);
			M.push_back(1);
		}
		V = V2;
	}

	int m = P.size();

	vector<vector<int>> PP(m);
	for (int i = 0; i < m; i++)
	{
		PP[i].resize(M[i] + 1);
		PP[i][0] = P[i];
		for (int j = 1; j <= M[i]; j++)
			PP[i][j] = PP[i][j - 1] * P[i];
	}

	int			d = 1;
	vector<int> I(m, 0);
	vector<int> D;
	do
		D.push_back(d);
	while (incr(I, d, M, PP));

	int ans = 2 * V + 1;
	for (int a : D)
	{
		int bc = V / a;
		for (int c = 1; c * c <= bc; c++)
			if (bc % c == 0)
				ans = min(ans, V / a + V / (bc / c) + V / c);
	}

	cout << 2 * ans;
}
