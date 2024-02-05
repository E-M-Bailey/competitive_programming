#include <bits/stdc++.h>

using namespace std;

int main()
{
	int64_t x;
	cin >> x;
	vector<int> P;
	for (int64_t i = 2; i * i <= x; i++)
	{
		if (x % i == 0)
		{
			P.push_back(1);
			do
			{
				P.back()++;
				x /= i;
			}
			while (x % i == 0);
		}
	}
	if (x > 1)
		P.push_back(2);
	sort(rbegin(P), rend(P));
	int			n = (int)P.size();
	vector<int> M(n + 1);
	M[0] = 1;
	for (int i = 0; i < n; i++)
		M[i + 1] = M[i] * P[i];
	int m = M.back();

	vector<int> I(n), J(n);
	vector<int> DP(m, INT_MIN);
	DP[0] = 0;
	for (int idx = 0; idx < m; idx++)
	{
		for (int i = 0; i < n; i++)
			J[i] = P[i] - 1;
		for (int jdx = m - 1;;)
		{
			DP[jdx] = max(DP[jdx], DP[jdx - idx] + 1);
			if (jdx == idx)
				break;
			for (int i = 0; i < n; i++)
			{
				if (jdx -= M[i], J[i]-- > I[i])
					break;
				else
				{
					J[i] = P[i] - 1;
					jdx += (P[i] - I[i]) * M[i];
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (++I[i] < P[i])
				break;
			else
				I[i] = 0;
		}
	}
	cout << DP.back() - 1;
}
