#include <bits/stdc++.h>

using namespace std;

void go();

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int x, y;
	cin >> x >> y;
	auto [X, Y] = minmax(x, y);
	cout << X << ' ' << Y << '\n';
}
