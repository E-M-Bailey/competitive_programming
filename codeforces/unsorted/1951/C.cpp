#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int		n;
	int64_t m, k;
	cin >> n >> m >> k;
	vector<int64_t> A(n);
	for (auto &a : A)
		cin >> a;
	sort(ALL(A));

	int64_t ans = k * (k - 1) / 2;
	for (auto a : A)
	{
		int64_t x = min(k, m);
		k -= x;
		ans += x * a - x * (x - 1) / 2;
	}
	cout << ans << '\n';
}
