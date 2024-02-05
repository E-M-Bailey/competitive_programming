#include <bits/stdc++.h>

using namespace std;

int ptime(string x)
{
	int X[6]{7, 6, 4, 3, 1, 0};
	for (int &xx : X)
		xx = x[xx] - '0';
	return X[0] + 10 * (X[1] + 6 * (X[2] + 10 * (X[3] + 6 * (X[4] + 10 * X[5]))));
}

int main()
{
	string A, B;
	cin >> A >> B;
	int a = ptime(A), b = ptime(B);
	if (b <= a)
		b += 24 * 60 * 60;
	int c = b - a;

	cout << (c / 60 / 60 / 10) << (c / 60 / 60 % 10) << ':' << (c / 60 / 10 % 6) << (c / 60 % 10) << ':' << (c / 10 % 6)
		 << (c % 10);
}
