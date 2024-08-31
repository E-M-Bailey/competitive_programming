
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
	int n;
	string s;
	cin >> n >> s;

	int ct = (int)count(ALL(s), '1');
	bool good = ct % 2 == 0;
	if (ct == 2 && s.find("11") != string::npos)
		good = false;
	if (!good)
		cout << "NO\n";
	else
		cout << "YES\n";
}
