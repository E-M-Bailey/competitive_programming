#include <bits/stdc++.h>

using namespace std;

typedef long double T;

constexpr int DIV = 1 << 15;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	while (cin >> n, n)
	{
		vector<T> A(n);
		for (auto &a : A)
			cin >> a;

		T sum  = accumulate(begin(A), end(A), T(0));
		T unit = sum / DIV;

		vector<int> B(n);
		for (int i = 0; i < n; i++)
			B[i] = (int)round(A[i] / unit);
		int m = accumulate(begin(B), end(B), 0);

		vector<int> P(m + 1, -2);
		P[0] = -1;
		for (int i = n - 1; i >= 0; i--)
		{
			int b = B[i];
			if (b == 0)
				continue;
			for (int j = m; j >= b; j--)
				if (P[j - b] >= -1)
					P[j] = i;
		}

		int best = -1;
		for (int s = 0; s <= m; s++)
			if (P[s] >= -1 && abs(2 * s - m) < abs(2 * best - m))
				best = s;

		vector<int> ans;
		int			p;
		while ((p = P[best]) >= 0)
		{
			ans.push_back(p);
			best -= B[p];
		}
		for (int a : ans)
			cout << a + 1 << ' ';
		cout << '\n';
	}
}
