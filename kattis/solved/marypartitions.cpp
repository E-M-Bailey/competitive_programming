#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int k, m, n;
		cin >> k >> m >> n;
		vector<uint32_t> A(n + 1, 1);
		for (int p = m; p <= n; p *= m)
			for (int i = p; i <= n; i++)
				A[i] += A[i - p];
		cout << k << ' ' << A.back() << '\n';
	}
}
