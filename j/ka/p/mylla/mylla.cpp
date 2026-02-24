#include "template.hpp"

using namespace std;
using namespace abbrev;

namespace
{

}

int main()
{
	int n;
	str s;
	cin >> n >> s;
	int a = 0, h = 0, aa = 0, hh = 0;
	for (char c : s)
	{
		a += c == 'A';
		h += c == 'H';
		if (max(a, h) == 3)
		{
			aa += a > h;
			hh += h > a;
			a = h = 0;
			if (max(aa, hh) == n)
				break;
		}
	}
	cout << (aa > hh ? "Hannes" : "Arnar");
}
