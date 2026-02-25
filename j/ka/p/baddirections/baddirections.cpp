#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, x;
	str s;
	cin >> n;
	while (n--)
	{
		cin >> x >> s;
		for (char &c : s)
			if ((c += x) > '9')
				c -= 10;
		cout << s << '\n';
	}
}
