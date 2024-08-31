#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<int> A(n);
		for (int &a : A)
			cin >> a;
		sort(begin(A), end(A));
		cout << A[n / 2] << '\n';
	}
}

