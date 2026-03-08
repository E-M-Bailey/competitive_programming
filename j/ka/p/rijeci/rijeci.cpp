#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int k;
	cin >> k;
	int a = 1, b = 0;
	while (k--)
		b += exchange(a, b);
	cout << a << ' ' << b;
}
