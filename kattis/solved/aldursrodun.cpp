#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	sort(begin(A), end(A));
	do
	{
		bool good = true;
		for (int i = 1; i < n; i++)
			good &= gcd(A[i - 1], A[i]) != 1;
		if (good)
		{
			for (int a : A)
				cout << a << ' ';
			return 0;
		}
	}
	while (next_permutation(begin(A), end(A)));
	cout << "Niebb";
}
