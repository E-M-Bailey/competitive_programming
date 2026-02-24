#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n;
	cin >> n;
	char px = 0, py = 0;
	int d = 0;
	str s;
	while (n--)
	{
		cin >> s;
		char x = s[0], y = s[1];
		if (px)
			d += abs(x - px) + abs(y - py);
		px = x;
		py = y;
	}
	cout << d;
}
