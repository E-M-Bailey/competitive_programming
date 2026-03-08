#include "template.hpp"

using namespace std;
namespace rng = ranges;
using namespace abbrev;

int main()
{
	str s;
	for (int n; cin >> n, n;)
	{
		cin >> s;
		rng::reverse(s);
		for (char &c : s)
		{
			int i = c == '_' ? 26 : c == '.' ? 27 : c - 'A';
			if ((i += n) >= 28)
				i -= 28;
			c = i == 26 ? '_' : i == 27 ? '.' : 'A' + i;
		}
		cout << s << '\n';
	}
}
