#include <bits/stdc++.h>

using namespace std;

int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int n;
		cin >> n;
		vector<int> A(2 * n);
		for (int &a : A)
			cin >> a;
		sort(begin(A), end(A));
		for (int i = 0; i < n; i++)
			A[i] = -A[i];
		cout << accumulate(begin(A), end(A), 0ll) << '\n';
	}
}
