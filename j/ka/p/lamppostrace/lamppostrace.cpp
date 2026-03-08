#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, x1 = 0, x2, d = 0;
	cin >> n;
	while (n--)
	{
		cin >> x2;
		d += abs(x2 - exchange(x1, x2));
	}
	cout << d;
}
