#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	u64 m = 0ull;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
		{
			char c;
			cin >> c;
			if (c == 'R')
				m |= (0x0101010101010101ull << j) | (0xffull << i * 8);
		}
	cout << popcount(~m);
}
