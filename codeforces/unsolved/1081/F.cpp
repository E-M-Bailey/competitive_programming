#include <bits/stdc++.h>

using namespace std;

int			   n, t;
pair<int, int> qry(int l, int r, bitset<300> &S)
{
	cout << "? " << l + 1 << ' ' << r << '\n' << flush;
	int q;
	cin >> q;
	if (q < 0)
		exit(0);
	int ans = 2 * q - n;
	int p	= (q + t) % 2;
	if (p == r % 2)
		for (int i = 0; i < r; i++)
			S[i] = !S[i];
	else
		for (int i = l; i < n; i++)
			S[i] = !S[i];
	t = q;
	return {ans, p};
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> n >> t;
	vector<int>			X(n);
	vector<bitset<300>> S(n);
	X[0] = 2 * t - n;
	for (int i = 1; i < n; i++)
	{
		S[i] = S[i - 1];
		int x, c;
		int a = n % 2 == 1 ? i % 2 == 1 ? i : 0 : i - 1;
		int b = n % 2 == 1 ? i % 2 == 1 ? n : i : i;
		int p = n % 2 == 0 && i % 2 == 1;
		do
			tie(x, c) = qry(a, b, S[i]);
		while (c != p);
		X[i] = x;
	}

	for (int i = 1; i < n; i++)
		if (S[i][n - 1])
		{
			for (int j = 0; j < n; j++)
				S[i][j] = !S[i][j];
			X[i] = -X[i];
		}

	for (int i = 1; i < n; i++)
		X[i] = (X[0] - X[i]) / 2;
	for (int i = 1; i < n; i++)
		for (int j = 1; j < i; j++)
			if (S[i][j - 1])
				X[i] -= X[j];
	for (int i = 1; i < n; i++)
		X[0] -= X[i];
	rotate(begin(X), begin(X) + 1, end(X));

	cout << "! ";
	for (int x : X)
		cout << (x == 1);
}
