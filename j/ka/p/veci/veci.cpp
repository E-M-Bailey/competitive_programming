#include "template.hpp"

using namespace std;
using namespace abbrev;

namespace
{
ai8<10> digs(int x)
{
	ai8<10> D{};
	do
		++D[x % 10];
	while (x /= 10);
	return D;
}
}

int main()
{
	int x, res = 0;
	cin >> x;
	auto D = digs(x);
	for (int y = x + 1; y < 10 * x; ++y)
		if (digs(y) == D)
		{
			res = y;
			break;
		}
	cout << res;
}
