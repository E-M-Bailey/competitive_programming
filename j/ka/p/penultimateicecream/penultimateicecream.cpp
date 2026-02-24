#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, a = 0, b = 0;
	cin >> n;
	while (n--)
	{
		int x;
		cin >> x;
		if (x > a)
			swap(a, x);
		if (x > b)
			swap(b, x);
	}
	cout << b;
}
