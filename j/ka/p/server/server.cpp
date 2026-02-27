#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, T, k = 0, t;
	cin >> n >> T;
	while (n--)
	{
		cin >> t;
		if ((T -= t) < 0)
			break;
		++k;
	}
	cout << k;
}
