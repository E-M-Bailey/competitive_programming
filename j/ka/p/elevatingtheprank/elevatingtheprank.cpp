#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int a, b, n, x;
	cin >> a >> b >> n;
	a += 10;
	b += 10;
	u64 m = 0;
	while (n--)
	{
		cin >> x;
		m |= 1ull << (x + 10);
	}
	// m &= ((1ull << a) - 1) ^ ((1ull << b) - 1);
	cout << abs(a - b) * 4 + popcount(m & (((1ull << a) - 1) ^ ((1ull << b) - 1) ^ (1ull << min(a, b)))) * 10;
}
