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

void go()
{
	int m;
	int n;
	string s;
	cin >> n >> m >> s;
	int F[7]{};
	for (char c : s)
		F[c - 'A']++;
	int ans = 0;
	for (int &f : F)
		ans += max(m - f, 0);
	
	cout << ans << '\n';
}
