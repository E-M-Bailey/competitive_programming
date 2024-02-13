#include <bits/stdc++.h>

using namespace std;

int main()
{
	int v, n;
	cin >> v >> n;
	while (n--)
	{
		string s;
		int w;
		cin >> s >> w;
		cout << s << ' ' << (v <= w ? "opin\n" : "lokud\n");
	}
}
