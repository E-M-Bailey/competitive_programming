#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, q;
	cin >> n >> q;
	vector<int> X(n);
	for (int &x : X)
		cin >> x;
	while (q--)
	{
		int c, a, b;
		cin >> c >> a >> b;
		if (c == 1)
			X[a - 1] = b;
		else
			cout << abs(X[a - 1] - X[b - 1]) << '\n';
	}
}
