#include <bits/stdc++.h>

using namespace std;

int main()
{
	int X[3], Y[3];
	for (int i = 0; i < 3; i++)
		cin >> X[i] >> Y[i];
	sort(begin(X), end(X));
	sort(begin(Y), end(Y));
	cout << (X[0] == X[1] ? X[2] : X[0]) << ' ' << (Y[0] == Y[1] ? Y[2] : Y[0]);
}
