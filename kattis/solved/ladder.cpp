#include <bits/stdc++.h>

using namespace std;

int main()
{
	double h, v;
	cin >> h >> v;
	cout << ceil(h / sin(v * (atan(1) / 45)));
}
