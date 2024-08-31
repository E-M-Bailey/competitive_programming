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
	int A, B, C, D;
	cin >> A >> B >> C >> D;
	auto [a, b] = minmax(A, B);
	auto [c, d] = minmax(C, D);
	if ((a < c && c < b && b < d) || (c < a && a < d && d < b))
		cout << "YES\n";
	else
		cout << "NO\n";
}
