#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<bitset<1 << 15>> A(n);
	vector<pair<int, int>>	X;
	for (auto &AA : A)
	{
		int k;
		cin >> k;
		X.resize(k);
		for (auto &[a, b] : X)
			cin >> a >> b;
		for (int mask = 0; mask < (1 << k); mask++)
		{
			int	 cur  = 0;
			bool good = true;
			for (int i = 0; i < k; i++)
			{
				int x = (mask & (1 << i) ? X[i].second : X[i].first) - 1;
				if (cur & (1 << x))
				{
					good = false;
					break;
				}
				cur |= 1 << x;
			}
			if (good)
				AA[cur] = true;
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++)
	{
		bitset<1 << 15> B;
		for (int j = 0; j < (1 << 15); j++)
			B[(1 << 15) - 1 - j] = A[i][j];
		for (int j = i + 1; j < n; j++)
			if (A[j] & B)
			{
				A[j].reset();
				
			}
	}
}
