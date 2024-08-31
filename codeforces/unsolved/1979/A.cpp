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

void go()
{
	int n;
	cin >> n;
	int ans = INT_MAX;
	int p;
	cin >> p;
	for (int i = 1; i < n; i++)
	{
		int a;
		cin >> a;
		ans = min(ans, max(p, a));
		p	= a;
	}
	cout << ans - 1 << '\n';
}
