#include "template.hpp"

using namespace std;
using namespace abbrev;


int main()
{
	int n;
	cin >> n;
	for (;;)
	{
		++n;
		if (!to_string(n * n).contains('6'))
			break;
	}
	cout << n;
}
