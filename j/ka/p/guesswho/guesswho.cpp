#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, m, q;
	cin >> n >> m >> q;
	vu32 C(n);
	str s;
	for (u32 &c : C)
	{
		cin >> s;
		for (int i = 0; i < m; ++i)
			c |= (s[i] == 'N') << i;
		c = (c << 16) | (c ^ 0xffffu);
	}
	u32 NY = 0;
	while (q--)
	{
		int i;
		char c;
		cin >> i >> c;
		NY |= 1u << (i - 1 + 16 * (c == 'Y'));
	}
	int id = 0, k = 0;
	for (int i = 0; i < n; ++i)
		if ((C[i] & NY) == 0)
		{
			++k;
			id = i + 1;
		}
	k == 1 ? cout << "unique\n" << id : cout << "ambiguous\n" << k;
}
