#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<vector<int>> PF(500);
	for (int i = 1; i < 500; i++)
	{
		int x = i;
		for (int j = 2; j < 500; j++)
			while (x % j == 0)
			{
				PF[i].push_back(j);
				x /= j;
			}
	}

	int n, k;
	while (cin >> n >> k)
	{
		vector<int> F(500);
		for (int i = 0; i < k; i++)
		{
			for (int p : PF[n - i])
				F[p]++;
			for (int p : PF[i + 1])
				F[p]--;
		}
		int64_t ans = 1;
		for (auto f : F)
			ans *= f + 1;
		cout << ans << '\n';
	}
}