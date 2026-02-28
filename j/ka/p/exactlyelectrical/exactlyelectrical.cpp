#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int a, b, c, d, t;
	cin >> a >> b >> c >> d >> t;
	int s = abs(a - c) + abs(b - d);
	cout << "NY"[s <= t && ((s ^ t) & 1) == 0];
}
