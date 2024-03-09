#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int a, b, c;
	cin >> a >> b >> c;
	if (a == 1 || c == 1 || (b == 2 && c == 2))
		cout << "What an excellent example!";
	else
		cout << "Oh look, a squirrel!";
}