#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, m, k;
		cin >> n >> k >> m;
		vector<int> A(n);
		for (int &a : A)
			cin >> a;
		sort(begin(A), end(A));
		map<int, int> I;
		int l = (k - 1) / 2;
		int i = 0;
		if (k % 2)
		{
			while (i < n && (A[i] != m || l > i || i >= n - l))
				i++;
			cout << (i < n ? "TAK\n" : "NIE\n");
		}
		else
		{
			map<int, int>::iterator jt;
			while (i < n && ((jt = I.find(2 * m - A[i])) == I.end() || l > jt->second || i >= n - l))
			{
				I[A[i]] = i;
				i++;
			}
			cout << (i < n ? "TAK\n" : "NIE\n");
		}
		// cout << i << '\n';
	}
}

