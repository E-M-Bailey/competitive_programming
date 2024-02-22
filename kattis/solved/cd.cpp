#include <bits/stdc++.h>

using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int			n, m;
	vector<int> A;
	A.reserve(2000000);
	while (cin >> n >> m, n)
	{
		A.resize(n + m);
		for (int &a : A)
			cin >> a;
		inplace_merge(begin(A), begin(A) + n, end(A));
		cout << end(A) - unique(begin(A), end(A)) << '\n';
	}
}
