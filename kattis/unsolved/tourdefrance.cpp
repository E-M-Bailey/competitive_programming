#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	while (cin >> n, n)
	{
		cin >> m;
		vector<int> A(n);
		for (int &a : A)
			cin >> a;
		vector<double> B;
		for (int i = 0; i < m; i++)
		{
			double x;
			cin >> x;
			for (int a : A)
				B.push_back(x / a);
		}
		sort(begin(B), end(B));
		double ans = 0;
		for (int i = 1; i < n * m; i++)
			ans = max(ans, B[i] / B[i - 1]);
		cout << fixed << setprecision(2) << ans << '\n';
	}
}
