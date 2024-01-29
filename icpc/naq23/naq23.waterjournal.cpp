#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, a, b;
	cin >> n >> a >> b;
	vector<int> A(n - 1);
	for (int &x : A)
		cin >> x;
	auto [mn, mx] = minmax_element(begin(A), end(A));
	bool m = a != *mn, M = b != *mx;
	if (*mn < a || *mx > b || (a < b && m && M))
		cout << "-1";
	else if (a == b)
		cout << a;
	else if (m)
		cout << a;
	else if (M)
		cout << b;
	else
		for (int i = a; i <= b; i++)
			cout << i << '\n';
}