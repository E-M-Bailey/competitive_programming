#include <bits/stdc++.h>

using namespace std;

#define sz(C) (int(size(C)))
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

bool has(int l, int r, int b)
{
	return (l & b) || (r & b) || ((r & ~(b - 1)) ^ (l & ~(b - 1)));
}

void go()
{
	int n, m;
	cin >> n >> m;
	int ans = 0;
	for (int b = 0; b <= 30; b++)
		if (has(max(0, n - m), n + m, 1 << b))
			ans |= 1 << b;
	cout << ans << '\n';
}
