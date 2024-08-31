#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1 && false)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

char qry(int a, int b, int c, int d)
{
	cout << "? " << a << ' ' << b << ' ' << c << ' ' << d << '\n' << flush;
	char ans;
	cin >> ans;
	return ans;
}

void go()
{
	int n;
	cin >> n;

	int mx = 0;
	for (int i = 1; i < n; i++)
		if (qry(i, i, mx, mx) == '>')
			mx = i;

	int cmp = 0;
	for (int i = 1; i < n; i++)
	{
		char q1 = qry(i, mx, cmp, mx);
		if (q1 == '>' || (q1 == '=' && qry(i, i, cmp, cmp) == '<'))
			cmp = i;
	}

	cout << "! " << mx << ' ' << cmp << '\n' << flush;
}
