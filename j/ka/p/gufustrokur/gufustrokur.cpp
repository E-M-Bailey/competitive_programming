#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int a, b;
	cin >> a >> b;
	int d = abs(a - b);
	cout << min(d, 360 - d);
}
