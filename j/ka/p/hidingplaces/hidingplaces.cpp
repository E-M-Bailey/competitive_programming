#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin >> n;
	while (n--)
	{
		str s;
		cin >> s;
		u64 m = 1ull << (s[0] - 'a' + ('8' - s[1]) * 8), pm;
		int k = 0;
		while (m != -1ull)
		{
			++k;
			pm = m;
			m |= ((m & 0xfefefefefefefefeull) >> 17) |
				((m & 0x7f7f7f7f7f7f7f7full) >> 15) |
				((m & 0xfcfcfcfcfcfcfcfcull) >> 10) |
				((m & 0x3f3f3f3f3f3f3f3full) >> 6) |
				((m & 0xfcfcfcfcfcfcfcfcull) << 6) |
				((m & 0x3f3f3f3f3f3f3f3full) << 10) |
				((m & 0xfefefefefefefefeull) << 15) |
				((m & 0x7f7f7f7f7f7f7f7full) << 17);
		}
		m ^= pm;
		cout << k;
		s = str(3, ' ');
		for (; m; m &= m - 1)
		{
			int i = countr_zero(m);
			s[1] = 'a' + i % 8;
			s[2] = '8' - i / 8;
			cout << s;
		}
		cout << '\n';
	}
}
