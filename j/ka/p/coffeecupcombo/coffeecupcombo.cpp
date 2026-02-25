#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, c = 0, k = 0;
	cin >> n;
	while (n--)
	{
		char ch;
		cin >> ch;
		if (ch == '1')
			c = 3;
		k += c-- > 0;
	}
	cout << k;
}
