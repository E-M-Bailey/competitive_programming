#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;
	A.insert(begin(A), -1);

	if (is_sorted(begin(A), end(A)))
	{
		cout << (ll)n * (2 * n + 1) << '\n';
		return;
	}

	int ls = -1, rs = n;
	while (A[ls + 1] == ls + 1)
		ls++;
	while (A[rs - 1] == rs - 1)
		rs--;

	int p = -1;
	for (int i = 1; i <= n; i++)
	{
		if (A[i] == i)
			continue;
		if (A[A[i]] != i)
		{
			p = -2;
			break;
		}
		int d = A[i] + i;
		if (d == p)
			continue;
		if (p >= 0 && d != p)
		{
			p = -2;
			break;
		}
		p = d;
	}

	ll ans = 0;
	for (int l = 1, r = 1; l <= ls + n; l++)
	{
		if (r < l)
			r++;
		if (r == l && r != p)
			r++;
		if ()
	}
}
