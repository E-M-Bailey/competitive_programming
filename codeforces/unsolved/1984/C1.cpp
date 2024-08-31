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
	long long a = 0, b = 0;
	while (n--)
	{
		int x;
		cin >> x;
		auto [a2, b2] = minmax({a + x, b + x, abs(a + x), abs(b + x)});
		tie(a, b)	  = pair{a2, b2};
	}
	cout << b << '\n';
}
