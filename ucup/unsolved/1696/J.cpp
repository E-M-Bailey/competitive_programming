#include <bits/stdc++.h>

using namespace std;

mt19937_64 randy(10239581324);

int main()
{
	int n;
	cin >> n;

	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	vector<bitset<1000000>> B(n + 1);
	B[0][0] = true;
	for (int i = 0; i < n; i++)
	{
		int a = A[i] % 1000000;
		int b = 1000000 - a;
		B[i + 1] = B[i] | (B[i] << a) | (B[i] >> b);
	}

	vector<int> ans;
	bernoulli_distribution distr;

	for (;;)
	{
		ans.clear();
		int i = n, x = 0, s = 0;
		while (i > 0 && s <= 1000000000)
		{
			i--;
			int aa = A[i], a = aa % 1000000;
			int pr = x - a;
			if (pr < 0)
				pr += 1000000;
			bool can = B[i][pr] && s + aa <= 1000000000;
			if (can && distr(randy))
			{
				ans.push_back(i);
				x = pr;
				s += aa;
			}
		}
		if (s == 1000000000)
		{
			cout << size(ans);
			for (int a : ans)
				cout << ' ' << a + 1;
			return 0;
		}
	}
}
