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

	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		go();
	}
}

void go()
{
	int n;
	cin >> n;
	int pos = 0, lo = 0, hi = 0;
	while (n--)
	{
		char c;
		cin >> c;
		if ((c ^ pos) & 1)
			hi = max(hi, ++pos);
		else
			lo = min(lo, --pos);
	}
	cout << hi - lo << '\n';
}
