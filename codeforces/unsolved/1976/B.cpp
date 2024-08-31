#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

typedef long long ll;

void go()
{
	int n;
	cin >> n;
	vector<int> A(n), B(n);
	int			l;
	for (int &a : A)
		cin >> a;
	for (int &b : B)
		cin >> b;
	cin >> l;
	ll ans = 0;
	int e = INT_MAX;
	for (int i = 0; i < n; i++)
	{
		ans += abs(A[i] - B[i]);
		if (min(A[i], B[i]) <= l && l <= max(A[i], B[i]))
			e = 0;
		e = min({e, abs(A[i] - l), abs(B[i] - l)});
	}
	cout << ans + e + 1 << '\n';
}
