#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int g, n, c = 2;
	cin >> g >> n;
	while (n--)
	{
		int a, b;
		cin >> a >> b;
		if (c == a)
			c = b;
		else if (c == b)
			c = a;
	}
	if (g != c)
		cout << g << ' ' << c;
	else if (g == 1)
		cout << "2 3";
	else if (g == 2)
		cout << "1 3";
	else
		cout << "1 2";
}
