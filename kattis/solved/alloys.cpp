#include <bits/stdc++.h>

using namespace std;

int main()
{
	float x;
	cin >> x;
	x = min(x, 1.f);
	cout << fixed << setprecision(6) << x * x / 4;
}