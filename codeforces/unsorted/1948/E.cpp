#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin.tie(0)->sync_with_stdio(0);
	int t = 1;
	cin >> t;
	while (t--)
	{
		go();
	}
}

void go()
{
	int n, k;
	cin >> n >> k;

	vector<int> A(n);
	iota(begin(A), end(A), 0);
	vector<int> C(n);
	int			ans = 0;

	for (int l = 0; l < n; l += k)
	{
		int r = min(l + k, n);
		fill(begin(C) + l, begin(C) + r, ans);
		ans++;

		int mid = (l + r) / 2;
		reverse(begin(A) + l, begin(A) + mid);
		reverse(begin(A) + mid, begin(A) + r);
	}

	for (int a : A)
		cout << a + 1 << ' ';
	cout << '\n' << ans << '\n';
	for (int c : C)
		cout << c + 1 << ' ';
	cout << '\n';
}
