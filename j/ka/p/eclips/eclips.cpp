#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str s, t = "oh noes";
	while (cin >> s)
		if (s.contains('e'))
		{
			t.clear();
			cout << s << ' ';
		}
	cout << t;
}
