#include "template.hpp"

using namespace std;
using namespace abbrev;

int main()
{
	str s, t;
	cin >> s >> t;
	int k = 1;
	for (int i = 0; i < 4; ++i)
		k *= 1 + (s[i] != t[i]);
	cout << k;
}
