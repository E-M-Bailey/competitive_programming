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
	int	   n;
	string s;
	cin >> n >> s;
	int ans = 0;
	for (int i = 0; i + 3 <= n;)
	{
		if (i + 5 <= n && s.substr(i, 5) == "mapie")
		{
			ans++;
			i += 5;
		}
		else if (s.substr(i, 3) == "map" || s.substr(i, 3) == "pie")
		{
			ans++;
			i += 3;
		}
		else
			i++;
	}
	cout << ans << '\n';
}
