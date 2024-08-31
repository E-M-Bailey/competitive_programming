#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n, m;
		cin >> n >> m;
		vector<int> A;
		int			z = 0;
		for (int i = 0; i < n; i++)
		{
			int a;
			cin >> a;
			if (a)
				A.push_back(a);
			else
				z++;
		}
		if (m == n)
			cout << "Richman\n";
		else if (m < z)
			cout << "Impossible\n";
		else
		{
			m -= z;
			cout << accumulate(begin(A), begin(A) + m, 0ll) + *min_element(begin(A) + m, end(A)) - 1 << '\n';
		}
	}
}