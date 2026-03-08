#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int k;
	cin >> k;
	--k;
	ai32<100> P;
	P.fill(-1);
	str ln;
	getline(cin, ln);
	for (;;)
	{
		getline(cin, ln);
		istringstream is(ln);
		int a, b;
		is >> a;
		if (--a < 0)
			break;
		while (is >> b)
			P[--b] = a;
	}
	while (k >= 0)
		cout << exchange(k, P[k]) + 1 << ' ';
}
