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
	int n;
	cin >> n;
	if (n % 2 == 0)
	{
		cout << "YES\n";
		char c = 'B';
		for (int i = 0; i < n; i += 2)
		{
			cout << c << c;
			c ^= 1;
		}
		cout << '\n';
	}
	else
		cout << "NO\n";
}
