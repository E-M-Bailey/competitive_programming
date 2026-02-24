#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int r, c;
	cin >> r >> c;
	str s(c, '\0');
	while (r--)
		for (char &ch : s)
		{
			char ch2;
			cin >> ch2;
			if (ch2 != '.')
				ch = ch2;
		}
	cout << s;
}
