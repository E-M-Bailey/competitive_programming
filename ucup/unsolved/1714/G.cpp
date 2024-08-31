#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<int> P(n);
		for (int &p : P)
		{
			cin >> p;
			p--;
		}
		vector<int>	 C;
		vector<bool> V(n, false);
		for (int i = 0; i < n; i++)
		{
			if (V[i])
				continue;
			C.clear();
			int j = i;
			do
			{
				C.push_back(j);
				V[j] = true;
				j	 = P[j];
			}
			while (j != i);

			for (int a : C)
				cout << a + 1 << ' ';
		}
		cout << '\n';
	}
}
