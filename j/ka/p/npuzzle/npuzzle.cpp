#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int d = 0;
	str s;
	for (int i = 0; i < 4; ++i)
	{
		cin >> s;
		for (int j = 0; j < 4; ++j)
		{
			if (s[j] == '.')
				continue;
			int c = s[j] - 'A';
			int i2 = c / 4, j2 = c % 4;
			d += abs(i - i2) + abs(j - j2);
		}
	}
	cout << d;
}
