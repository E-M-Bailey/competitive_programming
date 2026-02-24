#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	int n, x, m = 0;
	str s;
	cin >> n;
	while (n--)
	{
		cin >> x >> s;
		if (s == "nej")
			m = max(m, x);
	}
	cout << m;
}
