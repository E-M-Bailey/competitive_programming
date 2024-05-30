#include <bits/stdc++.h>

using namespace std;

int main()
{
	double v, a, t;
	cin >> v >> a >> t;
	cout << fixed << setprecision(7) << (v + a * t / 2) * t;
}
