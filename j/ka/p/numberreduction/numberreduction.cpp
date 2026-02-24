#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, k = 0;
	cin >> n;
	while (n > 1)
	{
		n = n % 2 ? 3 * n + 1 : n / 2;
		++k;
	}
	cout << k;
}
