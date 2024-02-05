#include <bits/stdc++.h>

using namespace std;

int main()
{
	int s, x, y, dx, dy;
	while (cin >> s >> x >> y >> dx >> dy, s)
	{
		bool fnd = false;
		for (int i = 0; i < 2 * s; i++)
		{
			int a = x % (2 * s), b = y % (2 * s);
			if (a > b)
				swap(a, b);
			if (0 < a && a < s && s < b && b < 2 * s)
			{
				cout << "After " << i << " jumps the flea lands at (" << x << ", " << y << ").\n";
				fnd = true;
				break;
			}
			x += dx;
			y += dy;
		}
		if (!fnd)
			cout << "The flea cannot escape from black squares.\n";
	}
}
