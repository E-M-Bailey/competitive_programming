#include <bits/stdc++.h>

using namespace std;

int main()
{
	cout << "1 0 0\n0 1 0\n0 0 1\n1 1 1\n1 2 3\n" << flush;
	int a, b, c, abc, abbccc;
	cin >> a >> b >> c >> abc >> abbccc;

	if (a + b + c == abc)
		;
	else if (a + b * 2 + c * 3 == abbccc)
		;
	else if (a * 2 + b + abbccc == abc * 3)
		c = abc - a - b;
	else if (a - c + abbccc == abc * 2)
		b = abc - a - c;
	else
		a = abc - b - c;
	
	cout << a << ' ' << b << ' ' << c;
}
