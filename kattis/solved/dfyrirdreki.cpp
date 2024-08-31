#include <bits/stdc++.h>

using namespace std;

int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	int d = b * b - 4 * a * c;
	cout << (d >= 0) + (d > 0);
}
