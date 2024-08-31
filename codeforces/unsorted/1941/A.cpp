#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	while (t--)
		go();
}

void go()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> B(n), C(m);
	for (int &b : B)
		cin >> b;
	for (int &c : C)
		cin >> c;

	sort(ALL(C));

	int ans = 0;
	for (int b : B)
		// c <= k - b
		ans += int(upper_bound(ALL(C), k - b) - begin(C));

	cout << ans << '\n';
}
