#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str s;
	getline(cin, s);
	int k = 0;
	for (int i = -1; (i = s.find("certainly", i + 1)) != s.npos;)
		++k;
	cout << k;
}
