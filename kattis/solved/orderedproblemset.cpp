#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> A(n), B;
	for (int &a : A)
		cin >> a;
	bool good = false;
	for (int k = 2; k <= n; k++)
		if (n % k == 0)
		{
			int b = n / k;
			B.resize(k * 2);
			for (int j = 0; j < k; j++)
			{
				auto [x, y] = minmax_element(begin(A) + j * b, begin(A) + (j + 1) * b);
				tie(B[j * 2], B[j * 2 + 1]) = pair(*x - 1, *y);
			}
			if (is_sorted(begin(B), end(B)))
			{
				cout << k << '\n';
				good = true;
			}
		}
	if (!good)
		cout << -1;
}
