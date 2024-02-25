#include <bits/stdc++.h>

using namespace std;

int main()
{
	double x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	cout << fixed << setprecision(6) << abs(x1 - x2) * abs(y1 - y2);
}
